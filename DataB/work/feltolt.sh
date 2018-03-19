#!/bin/bash

echo jelszo > all.sql
cat drop.sql >> all.sql
cat create.sql >> all.sql
cat alter.sql >> all.sql
cat insert.sql >> all.sql

/home/itep/Programok/Oracle/sqlcl/bin/sql DB18_VARPET@//dboracle.itk.ppke.hu:1521/lab.itk.ppke.hu <all.sql