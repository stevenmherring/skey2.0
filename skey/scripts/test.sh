msg=`echo johndoe | ./src/skey 88 ka9q2 | tail -1`
echo $msg
pepsi="NOLL AMRA FEE HOST BELA DEFT"
if [ "$msg" != "$pepsi" ] ; then
        exit 1
else
        exit 0
fi
