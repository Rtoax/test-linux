# openssl passwd -6 123456
rootpw --iscrypted "$6$sAQc/OHDBLkDCrRa$A2rTq7Bxc.Gt.NjylqAmDdTk6UE/E91nKSLTszPRvBEThsIXoC01ELT2VS0uQxTz3j8o2VpUdEb0/eGR.FvWJ1"
# openssl passwd -6 123456
user --groups=wheel --name=rongtao --password="$6$7tUK/Ic.H0PMzllV$NA5o/8DKvYaamnAsU.ZBs7Q6z1tk46kquCD6OnGLOpjM2ktdLFjwiIgjMMVPALV19zf5QxCVBgwESIBiBrWn21" --iscrypted --gecos="rongtao"
# openssl passwd -6 123456
user                --name=user0 --password="$6$EAM63SxYUUL7VrWl$SRohYYz6EBXMfAqdbbxzrphlDvu//ENkcTiLw74bkRsIIoJnHaTDz.jJdwCebiFjh6n3YHI9B5l3uM79L7j4T1" --iscrypted --gecos="User0"
user                --name=user1 --password="123456"          --gecos="User1"
user --groups=wheel --name=user2 --password="123456"          --gecos="User2"
user --groups=wheel --name=user3 --password="User123456!"     --gecos="User3"
user --groups=wheel --name=user4 --password="User1234567890!" --gecos="User4"
user --groups=wheel --name=user5 --password="TXJ&jzyzqbx@123" --gecos="User5"
