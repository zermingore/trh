#!/bin/bash

# Script parsing a CSV-like file, outputs SQL statements to a file


# TODO
# [ ] Fetch categories / languages from schema
# [X] Generic number of translations (remove copy/paste; >2 translations)




SQL_INSERT="INSERT INTO words(id_language, id_category, name, date)\
 VALUES(__ID_LG__, __ID_CAT__, \"__NAME__\", \"1970-01-01 00:00:00\");"

SQL_INSERT_TR="INSERT INTO translations(id_word_src, id_word_dst) VALUES(\
 (SELECT id FROM words WHERE id_language=__ID_LG__ AND name=\"__NAME__\" AND id_category=__ID_CAT__),\
 last_insert_rowid());"


function main()
{
  if [[ $# != 1 ]]; then
    echo "Expecting a unique argument: source file"
    exit 1
  fi

  local content_file=$1
  if ! [[ -f $content_file ]]; then
    echo "Unreadable source file [$content_file]"
    exit 1
  fi

  echo "BEGIN TRANSACTION;" > "$0_statements.sql"
  echo -n > "$0_log"

  while read line; do
    if [[ $line =~ ^# || $line =~ ^$ ]]; then
      continue
    fi
    echo "$line"

    local tokens
    IFS="|" read -ra tokens <<< "$line"
    if [[ $((${#tokens[@]} % 3)) != 0 ]]; then
      echo "Skipping [$line]: Expecting groups of 3 tokens" | tee -a "$0_log"
      continue
    fi

    local id_lg1=""
    local id_cat1=""
    local name1=""
    local -i index=0
    while [[ $((index + 3)) -le ${#tokens[@]} ]]; do
      local lg=${tokens[index]}
      local cat=${tokens[index + 1]}
      local name=${tokens[index + 2]}

      if [[ $lg == "" || $cat == "" || $name == "" ]]; then
        echo "Invalid line [$line] (lg: [$lg] cat: [$cat] name: [$name])"
        break
      fi

      # Fetch data for each word
      id_lg=$(getLanguage "$lg")
      if [[ $? -ne 0 ]]; then
         echo "[$line] Error getting language: $id_lg" | tee -a "$0_log"
         exit 2
      fi

      id_cat=$(getCategory "$cat")
      if [[ $? -ne 0 ]]; then
        echo "[$line] Error getting category: $id_cat" | tee -a "$0_log"
        exit 2
      fi

      sql=$(echo "$SQL_INSERT" \
              | sed "s/__ID_LG__/$id_lg/" \
              | sed "s/__ID_CAT__/$id_cat/" \
              | sed "s/__NAME__/$name/" \
         )
      echo "$sql" >> "$0_statements.sql"


      if [[ $index == 0 ]]; then
        id_lg1="$id_lg"
        id_cat1="$id_cat"
        name1="$name"
      else
        sql=$(echo "$SQL_INSERT_TR" \
                | sed "s/__ID_LG__/$id_lg1/" \
                | sed "s/__ID_CAT__/$id_cat1/" \
                | sed "s/__NAME__/$name1/" \
           )
        echo "$sql" >> "$0_statements.sql"
      fi

      index=$((index + 3))
    done

  done < "$content_file"
  echo "COMMIT;" >> "$0_statements.sql"
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
