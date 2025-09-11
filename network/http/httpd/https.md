https
=====

# Config https

```bash
sudo dnf install -y mod_ssl openssl
openssl genrsa -out server.key 2048
openssl req -new -key server.key -out server.csr
#  You are about to be asked to enter information that will be incorporated
#  into your certificate request.
#  What you are about to enter is what is called a Distinguished Name or a DN.
#  There are quite a few fields but you can leave some blank
#  For some fields there will be a default value,
#  If you enter '.', the field will be left blank.
#  -----
#  Country Name (2 letter code) [XX]:ch
#  State or Province Name (full name) []:Beijing
#  Locality Name (eg, city) [Default City]:Beijing
#  Organization Name (eg, company) [Default Company Ltd]:CEC
#  Organizational Unit Name (eg, section) []:CESTC
#  Common Name (eg, your name or your server's hostname) []:FT-5000C
#  Email Address []:rongtao@cestc.cn
#
#  Please enter the following 'extra' attributes
#  to be sent with your certificate request
#  A challenge password []:1q2w3e
#  An optional company name []:cestc
openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt
sudo cp server.crt /etc/pki/tls/certs/
sudo cp server.key /etc/pki/tls/private/
sudo cp server.csr /etc/pki/tls/private/
sudo vim /etc/httpd/conf.d/ssl.conf
#  SSLCertificateFile /etc/pki/tls/certs/server.crt
#  SSLCertificateKeyFile /etc/pki/tls/private/server.key
#  SSLCertificateChainFile /etc/pki/tls/private/server.csr
sudo systemctl restart httpd.service
```
