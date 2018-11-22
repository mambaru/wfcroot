#!/bin/bash
if [ -f ".git" ]; then
  echo "Ошибка! Не нужно запускать это в субмодуле. Склонируйте этот проект в отдельную директорию."
  exit 1
fi

if [ ! -d ".git" ]; then
  echo "Ошибка! Этот скрипт нужно запускать только в корневой папке проекта."
  exit 1
fi

if [ -d "wfcroot" ]; then
  echo "Ошибка! Этот скрипт работает только с библиотеками и не подходит для демонов."
  exit 1
fi

if ! git diff-index --quiet HEAD -- ; then
  echo "Ошибка! У вас есть не зафиксированные изменения! Сделайте git commit и повторно запустите этот скрипт"
  exit 1
fi

interactive_merge () {
  target=$(basename -- "$1")
  sdiff -sw 130 -o "${target}.tmp" "$2" "$1"
  if [ $? -eq 2 ]; then
    echo "Отмена! слияния ${target}"
    rm -f "${target}.tmp"
  else
    mv "${target}.tmp" "$2"
    cp "$2" "$3"
    echo "Слито! ${target}"
  fi
}

see_changes () {
  target=$(basename -- "$1")
  if ! diff "$2" "$1"; then
    echo "Выше показаны изменения в обновленном ${target} относительно твоего."
    echo "Как обычно у тебя три опции:"
    
    case1="Не обновлять. Оставить старый ${target} (с твоими изменениями)"
    case2="Принять новый ${target} (с потерей твоих изменений)"
    case3="Интерактивно слить с помощью sdiff (далее 1 - это твои, 2 - новые)"
    
    COLUMNS=12
    select yn in "${case1}" "${case2}" "${case3}"
    do
      case $yn in
        "${case1}" )
            echo "Файл ${target} без обновлений"
            break;;
        "${case2}" )
            cp "$1" "$2"
            cp "$1" "$3"
            echo "Файл ${target} заменен с потерей изменений"
            break;;
        "${case3}" )
            interactive_merge $1 $2 $3
            cp "$1" "$3"
            break;;
        * ) echo "Не тупи! 1,2 или 3"
      esac
    done
  else
    echo "Файлы ${target} в обновлении и локальные идентичны"
    cp "$1" "$3"
  fi
}

see_update () {
  target=$(basename -- "$1")

  echo "У мне две новости, дорогой друг. Первая заключается в том что прилетело "
  echo "обновление для ${target}. Вторая - ты внес в ${target} некоторые изменения."
  echo "Выше показаны изменения обновления (без учета твоих изменений)."
   
  case1="Не обновлять. Оставить старый ${target} (с твоими изменениями)."
  case2="Принять новый ${target} (с потерей твоих изменений)."
  case3="Посмотреть мои изменения."
    
  COLUMNS=12
  select yn in "${case1}" "${case2}" "${case3}"
  do
    case $yn in
      "${case1}" ) 
          echo "Файл ${target} без обновлений"
          break;;
      "${case2}" )
          echo "Файл ${target} заменен с потерей изменений"
          cp "$1" "$2"
          cp "$1" "$3"
          break;;
      "${case3}" )
          see_changes $1 $2 $3
          break;;
      * ) echo "Не тупи! 1,2 или 3"
    esac
  done
}

update_if () {
  target=$1
  if cmp -s "$2" "$3" ; then
    # Нет локальных изменений
    cp "$1" "$2"
    cp "$1" "$3"
    echo "Файл ${target} обновлен"
  else
    see_update $1 $2 $3
  fi
}

update_file () {
  target=$(basename -- "$1")
  if [ -L "$2" ]; then
    echo "удаляем ссылку $2"
    rm "$2"
  else
    echo "Это не ссылка $2"
  fi
  # проверяем пришло ли обновление 
  if [ ! -e ${target} ]; then
    # сохраняем файл и оригинал для сравнения при следующем update
    echo "Новый файл ${target}"
    cp "$1" "$2"
    cp "$1" "$3"
  elif [ ! -e "$3" ]; then
    echo "Прилетело обновление на новый файл ${target}, который у вас уже существует"
    see_changes $1 $2 $3
  elif diff "$1" "$3"; then
    echo "Файл ${target} без обновлений"
  else
    # обновляем файл, если нет локальных изменений, либо опрос
    update_if $1 $2 $3
  fi
}

echo "你好亲爱的朋友！"
echo "Этот скрипт подготовит ваш проект (библиотеку) для непрерывной сборки в gitlab-ci."
echo "Убедитесь, что вы запускаете его из корневой директории проекта. Если проект уже "
echo "подготовлен, то он будет обновлен до последней версии из master (бранч можно указать "
echo "первым аргументом). По завершению работы скрипта будет добавлен git submodule external/cmake-ci "
echo "и обновлены некоторые файлы. Продолжаем?"

select yn in "Yes" "No"
do
  case $yn in
      Yes ) break;;
      No ) exit;;
      * ) echo "Вот ты лопух! Зачем всякую дичь печатаешь? Надо число '1' или '2', что не понятно? Уверен что в состоянии дальше продолжать?"
  esac
done

branch="master"
[ ! -z $1 ] && branch=$1
echo "branch=$branch"
if [ ! -d "external/cmake-ci" ]; then
  git submodule add git@github.lan:cpp/cmake-ci.git external/cmake-ci || exit
else
  git submodule update --init --force -- external/cmake-ci || exit
  pushd external/cmake-ci
  git checkout $branch || exit
  git pull origin $branch
  popd
fi

mkdir -p .ci
mkdir -p .ci/orig
mkdir -p cmake
echo http://github.lan/cpp/cmake-ci/blob/master/Readme.md
[ ! -f ".ci/suppressions.txt" ] && touch ".ci/suppressions.txt"

update_file "./external/cmake-ci/root/Doxyfile"          "Doxyfile"          ".ci/orig/Doxyfile.orig" 
update_file "./external/cmake-ci/root/Makefile"          "Makefile"          ".ci/orig/Makefile.orig" 
update_file "./external/cmake-ci/root/customdoxygen.css" "customdoxygen.css" ".ci/orig/customdoxygen.css.orig" 
update_file "./external/cmake-ci/root/.gitlab-ci.yml"    ".gitlab-ci.yml"    ".ci/orig/.gitlab-ci.yml.orig"
update_file "./external/cmake-ci/root/.travis.yml"       ".travis.yml"       ".ci/orig/.travis.yml.orig"
update_file "./external/cmake-ci/cmake/ci.cmake"         "cmake/ci.cmake"    ".ci/orig/ci.cmake.orig" 
update_file "./external/cmake-ci/ci/automr.sh"           ".ci/automr.sh"          ".ci/orig/automr.sh.orig"
update_file "./external/cmake-ci/ci/cppcheck.sh"         ".ci/cppcheck.sh"        ".ci/orig/cppcheck.sh.orig"
update_file "./external/cmake-ci/ci/cppcheck-ci.sh"      ".ci/cppcheck-ci.sh"     ".ci/orig/cppcheck-ci.sh.orig"
update_file "./external/cmake-ci/ci/build-and-test.sh"   ".ci/build-and-test.sh"  ".ci/orig/build-and-test.sh.orig"
update_file "./external/cmake-ci/ci/build-and-test-spare.sh"   ".ci/build-and-test-spare.sh"  ".ci/orig/build-and-test-spare.sh.orig"

rm -- "$PWD/upgrade.sh"
git add .
if git commit -am "cmake-ci upgrade autocommit"; then
  echo "Все изменения автоматически зафиксированы. Для отмены, наберите: "
  echo "  git reset --hard HEAD~1"
fi
echo "Дальнейшие инструкции найдете здесь:"
echo "  http://github.lan/cpp/cmake-ci/blob/master/Readme.md"
echo Done
exit 0
