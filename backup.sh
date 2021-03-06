#!/bin/bash                                          

myuser=root
mypass=1234

args="-u"$myuser" -p"$mypass" --add-drop-database --add-locks --create-options --complete-insert --comments --disable-keys --dump-date --extended-insert --quick --routines --triggers"                                                     

mysql -u$myuser -p$mypass -e 'show databases' | grep -Ev "(Database|information_schema)" > databases.list

echo "Se volcarán las siguientes bases de datos:"
mysql -u$myuser -p$mypass -e 'select table_schema "DATABASE",convert(sum(data_length+index_length)/1048576, decimal(6,2)) "SIZE (MB)" from information_schema.tables where table_schema!="information_schema" group by table_schema;'
CONT=1
while [ $CONT -eq 1 ]
do
        echo -n "¿Desea continuar? (S/N): "
        read -n 1 K
        [[ "$K" == "N" || "$K" == "n" ]] && { echo ""; exit 0; }
        [[ "$K" == "S" || "$K" == "s" ]] && { CONT=0; }
        echo ""
done

while read DB
do
        dump="dump_"$DB".sql"
        echo -n $dump"... "
        mysqldump ${args} $DB > $dump
        echo "OK."
done < databases.list

rm databases.lis
