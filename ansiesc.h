#pragma once

#define ESCLR "\033[0m"

#define ESBLD "\033[1m"
#define ESTHN "\033[2m"
#define ESITA "\033[3m"
#define ESULN "\033[4m"
#define ESBLN "\033[5m"
#define ESFBLN "\033[6m"
#define ESREV "\033[7m"
#define ESHID "\033[8m"
#define ESUDO "\033[9m"

#define ESCBLK "\033[30m"
#define ESCRED "\033[31m"
#define ESCGRN "\033[32m"
#define ESCYEL "\033[33m"
#define ESCBLU "\033[34m"
#define ESCMGN "\033[35m"
#define ESCCYN "\033[36m"
#define ESCWHT "\033[37m"

#define ESCBBLK "\033[40m"
#define ESCBRED "\033[41m"
#define ESCBGRN "\033[42m"
#define ESCBYEL "\033[43m"
#define ESCBBLU "\033[44m"
#define ESCBMGN "\033[45m"
#define ESCBCYN "\033[46m"
#define ESCBWHT "\033[47m"

#define ESCCODE(code) "\033[38;5;" #code "m"
#define ESCCODE_RGB(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"
