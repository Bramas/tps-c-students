
../bin/students list > /tmp/list.txt
diff /tmp/list.txt expected_outpout/list.txt

if [ $? = 0 ]; then
    echo "Tests list réussis"
else
    echo "Erreur"
fi

../bin/students search -i 123456789 > /tmp/search.txt
diff /tmp/search.txt expected_outpout/search.txt

if [ $? = 0 ]; then
    echo "Tests search réussis"
else
    echo "Erreur"
fi
