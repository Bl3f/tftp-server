TFTP-Server
===========

Ce projet est un projet scolaire @TELECOM Nancy. C'est un serveur TFTP qui ne fonctionne qu'en mode octet. Il y a deux modes d'opérations qui sont implémentés dans le serveur, l'opération RRQ qui est une lecture du client sur le serveur et l'opération WRQ qui est une écriture du client sur le serveur. Si vous souhaitez avoir plus d'informations concernant le protocole [TFTP](http://en.wikipedia.org/wiki/Trivial_File_Transfer_Protocol), le programme fonctionne sur le port 69 et il n'y a pas de bascule sur un autre port après la connexion effectuée. 

De plus pour l'installation du programme il faut garder à l'esprit que ce programme est un FTP simplifié donc il faut séparer le client du serveur. 

Installation
------------

1. Pour l'installation du client, récupérer le dossier *client*

     make client

2. Pour l'installation du serveur, récupérer le dossier *server*

     make server

3. Pour désinstaller

     make clean

Usage
-----

* Pour le client il faut spécifier les paramètres du transfert

     ./client @IPServer (RRQ/WRQ) filename octet

* Pour le serveur il est nécessaire d'être administrateur pour exécuter le programme

     sudo ./server

Authors
=======

Christophe Blefari et Claire Descombes
