control-tower
=======================

This repository is mainly a collection of scripts which serve 
the purpose of becoming the de-facto server software for the reis
weatherbox. Any test-benches and production code should be 
placed and tracked in this repository.

The main purpose of the server software is to collect server 
information from the scel weatherboxes and push that data to a 
database program (currently Postgresql), where it can be accessed 
and used. The overall goal of this project is to make an easy to use,
easily scalable and easily deployable piece of software for the 
scel lab. 
