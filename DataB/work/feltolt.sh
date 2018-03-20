#!/bin/bash

./merge.sh

echo "idejonajelszo" > fall.sql
cat all.sql >> fall.sql

/home/itep/Programok/Oracle/sqlcl/bin/sql DB18_VARPET@//dboracle.itk.ppke.hu:1521/lab.itk.ppke.hu <fall.sql >out.txt

rm fall.sql