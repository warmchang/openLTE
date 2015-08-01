#!/bin/sh

# Determine which interface to use
tmp_wlan0=$(ifconfig | grep -c wlan0)
tmp_eth0=$(ifconfig | grep -c eth0)
iface="0"
if [ $tmp_wlan0 -eq 1 ]; then
    iface="wlan0"
fi
if [ $tmp_eth0 -eq 1 ]; then
    iface="eth0"
fi
if [ $iface = "0" ]; then
    echo "NO KNOWN INTERFACE TO USE"
    exit 1
fi

# Enable IPTABLES
tmp_ipt_en=$(cat /etc/sysctl.conf | grep -c -x net.ipv4.ip_forward=1)
if [ $tmp_ipt_en -eq 0 ]; then
    printf "net.ipv4.ip_forward=1\n" >> /etc/sysctl.conf
    sysctl -p /etc/sysctl.conf
fi
modprobe ip_tables
modprobe ip_conntrack

# Setup IPTABLES
iptables -C FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
if [ $? -eq 1 ]; then
    iptables -I FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
fi
iptables -C FORWARD -i tun_openlte -o $iface -m conntrack --ctstate NEW -j ACCEPT
if [ $? -eq 1 ]; then
    iptables -I FORWARD -i tun_openlte -o $iface -m conntrack --ctstate NEW -j ACCEPT
fi
iptables -t nat -C POSTROUTING -o $iface -j MASQUERADE
if [ $? -eq 1 ]; then
    iptables -t nat -I POSTROUTING -o $iface -j MASQUERADE
fi
iptables-save > /etc/iptables_openlte.rules
printf "#!/bin/sh\niptables-restore < /etc/iptables_openlte.rules\nexit 0\n" > /etc/network/if-up.d/iptablesload
chmod +x /etc/network/if-up.d/iptablesload

# Give cap_net_admin capabilities to LTE_fdd_enodeb
tmp_loc=$(which LTE_fdd_enodeb)
setcap cap_net_admin=eip $tmp_loc

# Give global read/write permissions to /dev/net/tun
chmod 666 /dev/net/tun

# Remove all shared memories for message queues
rm -f /dev/shm/*_olmq
