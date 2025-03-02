#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

using namespace std;

// Constantes de couleur
const string CBK = "\033[30m";
const string CRE = "\033[31m";
const string CGR = "\033[32m";
const string CYE = "\033[33m";
const string CBL = "\033[34m";
const string CMA = "\033[35m";
const string CCY = "\033[36m";
const string CWH = "\033[37m";
const string CBD = "\033[1m";
const string CNC = "\033[0m";

string execCmd(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe) return "";

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}

string draw(int perc, int size) {
    const string FULL = "━";
    const string EMPTY = "━";
    string out;
    int inc = perc * size / 100;

    for (int v = 0; v < size; v++) {
        out += (v <= inc) ? CMA + FULL : CWH + EMPTY;
    }

    return out;
}

string getColorBar() {
    string c = "\033[0m\033[31m░▒";

    for (int i = 1; i <= 6; i++) {
        c += "\033[" + to_string(i + 41) + "m\033[" + to_string(i + 30) + "m█▓▒░";
    }

    return c + "\033[37m█\033[0m▒░";
}

int main() {
    // Informations système
    string name = getenv("USER");

    struct utsname uts;
    uname(&uts);
    string host = uts.nodename;

    // Commandes pour récupérer les informations
    string distro = execCmd("awk -F '\"' '/PRETTY_NAME/ { print $2 }' /etc/os-release");
    string packages = execCmd("pacman -Q | wc -l");
    // Correction de la commande WM qui avait une erreur de syntaxe
    string wm = execCmd("xprop -id $(xprop -root -notype | awk '$1==\"_NET_SUPPORTING_WM_CHECK:\"{print $5}') -notype -f _NET_WM_NAME 8t | grep \"WM_NAME\" | cut -f2 -d \"\\\"\"");
    string storage = execCmd("df -h --output=used / | awk 'NR == 2 { print $1 }'");
    string term = execCmd("ps -o comm= -p $(ps -o ppid= -p $(ps -o sid= -p $$))");
    string uptm = execCmd("uptime -p | sed -e 's/hour/hr/' -e 's/hours/hrs/' -e 's/minutes/mins/' -e 's/minute/min/' -e 's/up //'");
    string shell = execCmd("echo $SHELL | sed 's/.*\\///'");

    // Mesures système
    int c_lvl = stoi(execCmd("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage}'"));
    string CPU = CGR + "cpu" + CNC + " " + to_string(c_lvl) + "% " + draw(c_lvl, 14) + "\n";

    int ram_lvl = stoi(execCmd("free | awk '/Mem:/ {print int($3/$2 * 100.0)}'"));
    string RAM = CYE + "ram" + CNC + " " + to_string(ram_lvl) + "% " + draw(ram_lvl, 14) + "\n";

    int disk_lvl = stoi(execCmd("df -h | grep '/$' | tr -s ' ' | cut -d ' ' -f5 | sed 's/%//'"));
    string DISK = CCY + "disk" + CNC + " " + to_string(disk_lvl) + "% " + draw(disk_lvl, 14) + "\n";

    // Affichage du logo
    cout << CBD << "                  " << CBL << ".\n"
         << "                 " << CBL << "/ " << CMA << "\\\n"
         << "                " << CBL << "/   " << CMA << "\\\n"
         << "               " << CBL << "/^.   " << CMA << "\\\n"
         << "              " << CBL << "/  ." << CWH << "-" << CMA << ".  \\\n"
         << "             " << CBL << "/  (   " << CMA << ") _\\\n"
         << "            " << CBL << "/ *.~   " << CMA << "~.*^\\\n"
         << "           " << CBL << "/.^         " << CMA << "^.\\\n";

    cout << "\033[0m\n    " << getColorBar() << "\033[0m\n\n";

    // Affichage des informations utilisateur
    cout << "             Hi " << CRE << CBD << name << CNC << "\n"
         << "          Welcome to " << CGR << CBD << host << CNC << "\n"
         << "            up " << CCY << CBD << uptm << CNC << "\n\n";

    // Affichage des informations système
    cout << CRE << "         distro " << CWH << "⏹ " << CNC << distro << "\n"
         << CBL << "         kernel " << CWH << "⏹ " << CNC << uts.release << "\n"
         << CMA << "       packages " << CWH << "⏹ " << CNC << packages << "\n"
         << CGR << "          shell " << CWH << "⏹ " << CNC << shell << "\n"
         << CYE << "           term " << CWH << "⏹ " << CNC << term << "\n"
         << CCY << "             wm " << CWH << "⏹ " << CNC << wm << "\n"
         << CBL << "           disk " << CWH << "⏹ " << CNC << storage << " used\n"
         << CNC << "\n";

    // Affichage des barres de mesure
    cout << "        " << CPU
         << "        " << RAM
         << "       " << DISK;

    return 0;
}
