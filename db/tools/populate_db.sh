#!/bin/bash

# Script parsing a CSV-like file, outputs SQL statements to a file


# TODO
# [ ] Fetch categories / languages from schema
# [ ] More than 2 translations




SQL_INSERT="INSERT INTO words(id_language, id_category, name)\
 VALUES(__ID_LG__, __ID_CAT__, __NAME__);"

SQL_INSERT_ID="INSERT INTO words(id, id_language, id_category, name)\
 VALUES(__ID__, __ID_LG__, __ID_CAT__, __NAME__);"


echo -n > "$0_statements.sql"

while read line; do
  if [[ $line =~ ^# || $line =~ ^$ ]]; then
    continue
  fi
  echo "__ $line __"

  while IFS="|" read -r lg1 cat1 name1 lg2 cat2 name2 lg3 cat3 name3 rest; do
    # Sanity checks
    if [[ $rest != "" ]]; then
      echo "Ignoring Ill-formed line [$line] (unexpected [$rest])"
      echo "[TODO] handle more than 2 translations"
      break
    fi

    if [[ $lg1 == "" || $cat1 == "" || $name1 == "" ]]; then
      echo "Invalid line [$line] (lg: [$lg1] cat: [$cat1] name: [$name1])"
      break
    fi

    if [[ $lg2 != "" ]]; then
      if [[ $cat2 == "" || $name2 == "" ]]; then
        echo "Invalid line [$line] (lg2: [$lg2] cat2: [$cat2] name2: [$name2])"
        break
      fi
    fi

    if [[ $lg3 != "" ]]; then
      if [[ $cat3 == "" || $name3 == "" ]]; then
        echo "Invalid line [$line] (lg3: [$lg3] cat3: [$cat3] name3: [$name3])"
        break
      fi
    fi



    # Fetch data for each word
    id_lg=""
    if [[ $lg1 == "en" ]]; then
      id_lg="1"
    fi
    if [[ $lg1 == "de" ]]; then
      id_lg="2"
    fi
    if [[ $lg1 == "fr" ]]; then
      id_lg="3"
    fi
    if [[ $id_lg == "" ]]; then
      echo "invalid language $lg1"
      break
    fi



    id_cat="1" # unknown
    case "$cat1" in
      "unknown")
        id_cat="1"
        ;;

      "noun_masculine")
        id_cat="2"
        ;;

      "noun_feminine")
        id_cat="3"
        ;;

      "noun_neutral")
        id_cat="4"
        ;;

      "noun_plural")
        id_cat="5"
        ;;

      "pronoun")
        id_cat="6"
        ;;

      "verb")
        id_cat="7"
        ;;

      "adjective")
        id_cat="8"
        ;;

      "adverb")
        id_cat="9"
        ;;

      "conjunction")
        id_cat="10"
        ;;

      "preposition")
        id_cat="11"
        ;;

      "interjection")
        id_cat="12"
        ;;

      "sentence")
        id_cat="13"
        ;;

      "abreviation")
        id_cat="5"
        ;;

      "unknown")
        echo "Warning: Unknown category [$cat1] -> assigning unknown"
        id_cat="1"
        ;;
    esac


    sql=$(echo "$SQL_INSERT" \
            | sed "s/__ID_LG__/$id_lg/" \
            | sed "s/__ID_CAT__/$id_cat/" \
            | sed "s/__NAME__/$name1/" \
       )


    echo "$sql" >> "$0_statements.sql"



    # TODO
    echo "2: $lg2"
    echo "c: $cat2"
    echo "n: $name2"

    echo "3: $lg3"
    echo "c: $cat3"
    echo "n: $name3"
  done < <(echo "$line")

done < content
