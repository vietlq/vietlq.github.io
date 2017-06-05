+++
categories = []
date = "2017-06-05T13:49:58+01:00"
draft = true
tags = []
thumbnail = ""
title = "HPKP - HTTP Public Key Pinning"
description = "Learn how to install HPKP - HTTP Public Key Pinning"

+++

```
sudo cat /path/to/fullchain/cert.pem | openssl x509 -pubkey | openssl pkey -pubin -outform der | openssl dgst -sha256 -binary | base64
```

You will get something like this:

```
MHJYVThihUrJcxW6wcqyOISTXIsInsdj3xK8QrZbHec=
```

Now let's generate back-up pins:

```
sudo su
mkdir /etc/hpkp/code2.pro
chmod 0700 /etc/hpkp /etc/hpkp/code2.pro
cd /etc/hpkp/code2.pro
openssl genrsa -out code2.pro.first.key 4096
openssl genrsa -out code2.pro.second.key 4096
chmod 0600 *

openssl req -new -key code2.pro.first.key -sha256 -out code2.pro.first.csr
openssl req -new -key code2.pro.second.key -sha256 -out code2.pro.second.csr
chmod 0600 *
```

```
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:UK
State or Province Name (full name) [Some-State]:London
Locality Name (eg, city) []:London
Organization Name (eg, company) [Internet Widgits Pty Ltd]:Code2Pro
Organizational Unit Name (eg, section) []:IT
Common Name (e.g. server FQDN or YOUR name) []:code2.pro
Email Address []:viet@code2.pro
```

```
openssl req -pubkey < code2.pro.first.csr | openssl pkey -pubin -outform der | openssl dgst -sha256 -binary | base64

openssl req -pubkey < code2.pro.second.csr | openssl pkey -pubin -outform der | openssl dgst -sha256 -binary | base64
```

Follow instructions on the page https://gethttpsforfree.com/

```
PRIV_KEY=/path/to/private/key/code2.pro.key; echo -n "secret" | openssl dgst -sha256 -hex -sign $PRIV_KEY
```

http://simpleit.us/.well-known/acme-challenge/5i8iV4Z5annluGwlWxwexKC6AHNtbNUwr_sHTyn44cg

Update Apache config file for your `VirtualHost`:

```
<IfModule mod_ssl.c>
<VirtualHost *:443>
    ServerAdmin viet@code2.pro
    DocumentRoot /var/www/code2.pro/public

    ServerName code2.pro
    ServerAlias www.code2.pro
    <Directory /var/www/code2.pro/public/>
        AllowOverride all
    </Directory>

    Header always set Strict-Transport-Security "max-age=31536000; includeSubDomains"

    ErrorLog ${APACHE_LOG_DIR}/code2.pro.error.log
    CustomLog ${APACHE_LOG_DIR}/code2.pro.access.log combined
    SSLCertificateFile /path/to/fullchain/fullchain.pem
    SSLCertificateKeyFile /path/to/private/key/code2.pro.key
    Include /etc/letsencrypt/options-ssl-apache.conf

    Header always set Public-Key-Pins "pin-sha256=\"MHJYVThihUrJcxW6wcqyOISTXIsInsdj3xK8QrZbHec=\"; pin-sha256=\"11JYV22ihUrJc336w44yOI55XIs66sdj3xK8Q77bHec=\"; pin-sha256=\"22ert33ihUrJc336w88yOI77XIs99sdj3xK8Q00bKlm=\"; includeSubdomains; max-age=31536000"

</VirtualHost>
</IfModule>
```

https://securityheaders.io/?q=https%3A%2F%2Fcode2.pro%2F

## References

https://scotthelme.co.uk/hpkp-http-public-key-pinning/

https://scotthelme.co.uk/guidance-on-setting-up-hpkp/

https://gethttpsforfree.com/

https://support.rackspace.com/how-to/generate-a-csr-with-openssl/

https://community.letsencrypt.org/t/how-to-obtain-a-ssl-certificate-from-lets-encrypt-with-a-csr/15942/10

https://report-uri.io/home/pkp_analyse/https%3A%2F%2Fgithub.com

https://report-uri.io/home/analyse

https://geekflare.com/apache-web-server-hardening-security/

http://centminmod.com/http-public-key-pinning.html

https://www.ssllabs.com/ssltest/analyze.html?d=code2.pro&latest
