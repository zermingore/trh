#!/bin/bash

# Script parsing a CSV-like file, outputs SQL statements to a file


# TODO
# [ ] Fetch categories / languages from schema
# [ ] More than 2 translations




SQL_INSERT="INSERT INTO words(id_language, id_category, name)\
 VALUES(__ID_LG__, __ID_CAT__, \"__NAME__\");"

SQL_INSERT_TR="INSERT INTO translations(id_word_src, id_word_dst) VALUES(\
 (SELECT id FROM words WHERE id_language=__ID_LG__ AND name=\"__NAME__\" AND id_category=__ID_CAT__),\
 last_insert_rowid());"


function main()
{
  echo -n > "$0_statements.sql"
  echo -n > "$0_log"

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
      id_lg1=$(getLanguage "$lg1")
      if [[ $? -ne 0 ]]; then
         echo "[$line] Error getting language: $id_lg1" | tee -a "$0_log"
         exit 2
      fi

      id_cat1=$(getCategory "$cat1")
      if [[ $? -ne 0 ]]; then
        echo "[$line] Error getting category: $id_cat1" | tee -a "$0_log"
        exit 2
      fi

      sql=$(echo "$SQL_INSERT" \
              | sed "s/__ID_LG__/$id_lg1/" \
              | sed "s/__ID_CAT__/$id_cat1/" \
              | sed "s/__NAME__/$name1/" \
         )
      echo "$sql" >> "$0_statements.sql"



      if [[ $lg2 != "" ]];then
        id_lg=$(getLanguage "$lg2")
        if [[ $? -ne 0 ]]; then
          echo "[$line] Error getting language: $id_lg" | tee -a "$0_log"
          exit 2
        fi

        id_cat=$(getCategory "$cat2")
        if [[ $? -ne 0 ]]; then
          echo "[$line] Error getting category: $id_cat" | tee -a "$0_log"
          exit 2
        fi

        sql=$(echo "$SQL_INSERT" \
                | sed "s/__ID_LG__/$id_lg/" \
                | sed "s/__ID_CAT__/$id_cat/" \
                | sed "s/__NAME__/$name2/" \
           )
        echo "$sql" >> "$0_statements.sql"

        sql=$(echo "$SQL_INSERT_TR" \
                | sed "s/__ID_LG__/$id_lg1/" \
                | sed "s/__ID_CAT__/$id_cat1/" \
                | sed "s/__NAME__/$name1/" \
           )
        echo "$sql" >> "$0_statements.sql"
      fi



      if [[ $lg3 != "" ]];then
        id_lg=$(getLanguage "$lg3")
        if [[ $? -ne 0 ]]; then
          echo "[$line] Error getting language: $id_lg" | tee -a "$0_log"
          exit 2
        fi

        id_cat=$(getCategory "$cat3")
        if [[ $? -ne 0 ]]; then
          echo "[$line] Error getting category: $id_cat" | tee -a "$0_log"
          exit 2
        fi

        sql=$(echo "$SQL_INSERT" \
                | sed "s/__ID_LG__/$id_lg/" \
                | sed "s/__ID_CAT__/$id_cat/" \
                | sed "s/__NAME__/$name3/" \
           )
        echo "$sql" >> "$0_statements.sql"

        sql=$(echo "$SQL_INSERT_TR" \
                | sed "s/__ID_LG__/$id_lg1/" \
                | sed "s/__ID_CAT__/$id_cat1/" \
                | sed "s/__NAME__/$name1/" \
           )
        echo "$sql" >> "$0_statements.sql"
      fi


    done < <(echo "$line")

  done < content
}



function getLanguage()
{
  case "$1" in
    "en")
      echo 1
      ;;
    "de")
      echo 2
      ;;
    "fr")
      echo 3
      ;;
    *)
      echo "invalid language [$1]"
      return 1
      ;;
  esac
}



function getCategory()
{
  case "$1" in
    "unknown")
      echo 1
      ;;

    "noun_masculine")
      echo 2
      ;;

    "noun_feminine")
      echo 3
      ;;

    "noun_neutral")
      echo 4
      ;;

    "noun_plural")
      echo 5
      ;;

    "pronoun")
      echo 6
      ;;

    "verb")
      echo 7
      ;;

    "adjective")
      echo 8
      ;;

    "adverb")
      echo 9
      ;;

    "conjunction")
      echo 10
      ;;

    "preposition")
      echo 11
      ;;

    "interjection")
      echo 12
      ;;

    "sentence")
      echo 13
      ;;

    "abreviation")
      echo 14
      ;;

    *)
      echo "Unknown category [$cat1]"
      return 1
      ;;
  esac
}



main "$@"
