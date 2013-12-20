Anna-Lise
=========

Pré-requis
----------
### Nécessaire

- ```make```
- ```gcc```

#### Ubuntu
```bash
$ apt-get install build-essential git
```

#### Fedora
```bash
$ yum groupinstall "Development Tools"
$ yum install man-pages git
```

### Optionnel
#### Documentation

- ```doxygen```
- ```dot```

##### Ubuntu
```bash
$ apt-get install doxygen graphviz
```
##### Fedora
```bash
$ yum install doxygen graphviz
```

#### Tests
##### Ubuntu
```bash
$ apt-get install libcunit1 libcunit1-dev libcunit1-doc
```

##### Fedora
```bash
$ yum install CUnit CUnit-devel
```

Récuperer Anna-Lise
-------------------

```bash
$ git clone https://github.com/remove/Anna-Lise.git
```

Compiler et lancer Anna-Lise
----------------------------
```bash
$ make
$ [sudo] bin/anna-lise <hostname>
```

Documentation
-------------
Un fichier ```Doxyfile``` est déjà fourni. Pour générer la documentation :
```bash
$ doxygen
```
La documentation sera générée dans un dossier ```documentation```. Celle-ci est également disponible à cette [adresse](http://remove.github.io/Anna-Lise/ "Documentation").

Branches et tags
----------------
La branche ```master``` pointe sur la dernière version stable, tandis que la branche ```dev``` pointe sur la version de développement. Pour passer d'une branche à une autre :
```bash
$ git checkout <branche>
```

Les versions majeures également sont affublées de tags. Pour lister les tags :
```bash
$ git tag --list
```
Ensuite, pour passer à un tag particulier :
```bash
$ git checkout <tag>
```

License
-------
Copyright © 2013 Harenome RAZANAJATO, Jérémy MEYER

Ce projet est libre. Vous pouvez le redistribuer ou le modifier selon les termes de la license « Do What The Fuck You Want To Public License », Version 2, comme publiée par Sam Hocevar. Pour de plus amples informations, veuillez vous référer au fichier COPYING, ou bien http://www.wtfpl.net/.
