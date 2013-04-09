history | tr -s ' ' | cut -d " " -f 3 | sort | uniq -c | sort -gr | head
