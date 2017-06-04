+++
categories = []
date = "2017-06-04T21:07:05+01:00"
draft = false
tags = ["dev", "rabbitmq", "tips", "ubuntu", "mq"]
thumbnail = "pimages/00025-skin-tone-rabbits-background.jpg"
title = "install rabbitmq ubuntu 1604"

+++

Enable RabbitMQ application repository:

```
echo "deb http://www.rabbitmq.com/debian/ testing main" >> /etc/apt/sources.list
```

Add the verification key for the package:

```
curl http://www.rabbitmq.com/rabbitmq-signing-key-public.asc | sudo apt-key add -
```

Update the sources with our new addition from above:

```
apt-get update
```

And finally, download and install RabbitMQ:

```
sudo apt-get install rabbitmq-server
```

In order to manage the maximum amount of connections upon launch, open up and edit the following configuration file using nano and uncomment the line `ulimit`:

```
sudo nano /etc/default/rabbitmq-server
```

To enable `RabbitMQ Management Console`, run the following:

```
sudo rabbitmq-plugins enable rabbitmq_management
```

With `RabbitMQ Management Console` enabled, you can access it using a web browser via the port `15672`. Make sure that your firewall is up and allows only ports 22, 80, 443:

```
$ sudo ufw status

Status: active

To                         Action      From
--                         ------      ----
22/tcp                     ALLOW       Anywhere
80/tcp                     ALLOW       Anywhere
443/tcp                    ALLOW       Anywhere
22/tcp (v6)                ALLOW       Anywhere (v6)
80/tcp (v6)                ALLOW       Anywhere (v6)
443/tcp (v6)               ALLOW       Anywhere (v6)
```

I understand you are tempted to punch a hole to allow access to the port `15672`. There is a better way without lifting your firewall. To access from the local machine, better create a temporary SSH tunnel to your server:

```
ssh -N -L 15672:localhost:15672 code2.pro
```

Now use your favourite web browser and nagivate to http://localhost:15672/

##  References

* [ How To Install and Manage RabbitMQ](https://www.digitalocean.com/community/tutorials/how-to-install-and-manage-rabbitmq)
