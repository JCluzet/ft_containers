# define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

output=$(make re && ./container)

printf "Create new main with ft:: instead of std:: ...\n"

mv main.cpp mainback
cat mainback | sed 's/std::stack/ft::stack/g' > main.cpp

printf "Done !\n\n"
output2=$(make re && ./container)

diff=$(diff <(echo "$output") <(echo "$output2"))
printf "RESULT : "
# if diff is empty, then the two files are the same, else output diff
if [ -z "$diff" ]; then
    printf "$GREEN Test passed with same output :)$RESET\n\n"
else
    printf "$RED Test failed !$RESET\n"
    printf "$diff\n"
fi

printf "Restoring old version...\n"
rm main.cpp
mv mainback main.cpp