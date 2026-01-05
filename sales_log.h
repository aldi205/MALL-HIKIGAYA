#ifndef SALES_LOG_H
#define SALES_LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

namespace SalesLog {
    static const char* LOGFILE = "sales_log.txt";

    // get system timestamp: YYYY-MM-DD HH:MM:SS
    static std::string nowTimestamp() {
        std::time_t t = std::time(nullptr);
        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        tm = *std::localtime(&t);
#endif
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        return std::string(buf);
    }

    static std::string escape(const std::string &s) {
        std::string out;
        for (size_t i=0;i<s.size();++i) {
            char c = s[i];
            if (c == '\n') out += "\\n";
            else if (c == '|') out += '/';
            else out += c;
        }
        return out;
    }

    static std::string unescape(const std::string &s) {
        std::string out;
        for (size_t i=0;i<s.size();++i) {
            if (s[i] == '\\' && i+1 < s.size() && s[i+1] == 'n') { out += '\n'; ++i; }
            else out += s[i];
        }
        return out;
    }

    static void appendWithTimestamp(const std::string &ts, const std::string &buyer, const std::string &details, int total) {
        std::ofstream out(LOGFILE, std::ios::app);
        if (!out.is_open()) return;
        out << ts << '|' << buyer << '|' << total << '|' << escape(details) << '\n';
        out.close();
    }

    static void appendCurrent(const std::string &buyer, const std::string &details, int total) {
        appendWithTimestamp(nowTimestamp(), buyer, details, total);
    }

    static void printAll() {
        std::ifstream in(LOGFILE);
        if (!in.is_open()) { cout << "No sales log file.\n"; return; }
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back()=='\r') line.pop_back();
            size_t p1 = line.find('|'); if (p1==std::string::npos) continue;
            size_t p2 = line.find('|', p1+1); if (p2==std::string::npos) continue;
            size_t p3 = line.find('|', p2+1); if (p3==std::string::npos) continue;
            std::string ts = line.substr(0,p1);
            std::string buyer = line.substr(p1+1, p2-p1-1);
            std::string tot = line.substr(p2+1, p3-p2-1);
            std::string det = line.substr(p3+1);
            cout << "[" << ts << "] " << buyer << " - Rp " << tot << "\n";
            cout << unescape(det) << "\n";
            cout << "-------------------------\n";
        }
        in.close();
    }

    static int sumAll() {
        std::ifstream in(LOGFILE);
        if (!in.is_open()) return 0;
        std::string line; int sum = 0;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back()=='\r') line.pop_back();
            size_t p1 = line.find('|'); if (p1==std::string::npos) continue;
            size_t p2 = line.find('|', p1+1); if (p2==std::string::npos) continue;
            size_t p3 = line.find('|', p2+1); if (p3==std::string::npos) continue;
            std::string tot = line.substr(p2+1, p3-p2-1);
            try { sum += stoi(tot); } catch(...) {}
        }
        in.close();
        return sum;
    }

    static void filterByDatePrint(const std::string &date) {
        std::ifstream in(LOGFILE);
        if (!in.is_open()) { cout << "No sales log file.\n"; return; }
        std::string line; int sum = 0; bool found = false;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back()=='\r') line.pop_back();
            size_t p1 = line.find('|'); if (p1==std::string::npos) continue;
            std::string ts = line.substr(0,p1);
            if (ts.size() < 10) continue;
            if (ts.substr(0,10) == date) {
                found = true;
                size_t p2 = line.find('|', p1+1); if (p2==std::string::npos) continue;
                size_t p3 = line.find('|', p2+1); if (p3==std::string::npos) continue;
                std::string buyer = line.substr(p1+1, p2-p1-1);
                std::string tot = line.substr(p2+1, p3-p2-1);
                std::string det = line.substr(p3+1);
                cout << "[" << ts << "] " << buyer << " - Rp " << tot << "\n";
                cout << unescape(det) << "\n" << "-------------------------\n";
                try { sum += std::stoi(tot); } catch(...) {}
            }
        }
        in.close();
        if (!found) cout << "Tidak ada transaksi pada tanggal " << date << "\n";
        else cout << "Total pada " << date << ": Rp " << sum << "\n";
    }

    static void pruneKeepLast(int maxEntries) {
        std::ifstream in(LOGFILE);
        if (!in.is_open()) return;
        std::string* buf = new std::string[maxEntries];
        int count = 0; std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back()=='\r') line.pop_back();
            buf[count % maxEntries] = line; count++;
        }
        in.close();
        int start = count > maxEntries ? (count % maxEntries) : 0;
        int toWrite = count > maxEntries ? maxEntries : count;
        std::ofstream out(LOGFILE, std::ios::trunc);
        for (int i = 0; i < toWrite; i++) out << buf[(start + i) % maxEntries] << '\n';
        out.close(); delete[] buf;
    }

    static void interactiveMenu() {
        int p;
        do {
            cout << "\n===== CATATAN PENJUALAN =====\n";
           cout << "1. Lihat semua transaksi\n";
           cout << "2. Jumlahkan seluruh pendapatan\n";
            cout << "3. Cari transaksi per tanggal (YYYY-MM-DD)\n";
           cout << "4. Hapus catatan lebih dari 40 hari (hanya disimpan 500 entri)\n";
            cout << "0. Kembali\n";
            cout << "Pilih: "; cin >> p;
            if (p == 1) printAll();
            else if (p == 2) cout << "Total pendapatan: Rp " << sumAll() << "\n";
            else if (p == 3) { string date; cout << "Masukkan tanggal (YYYY-MM-DD): "; cin >> date; filterByDatePrint(date); }
            else if (p == 4) { pruneKeepLast(200); cout << "Prune selesai. Hanya disimpan 200 entri terakhir.\n"; }
        } while (p != 0);
    }

}

#endif
#ifndef SALES_LOG_H
#define SALES_LOG_H

#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iostream>

struct SalesEntry {
    std::string date; // YYYY-MM-DD
    std::string buyer;
    int total;
    std::string details;
};

namespace SalesLog {
    static const char* LOGFILE = "sales_log.txt";

    static std::string todayDate() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
        return std::string(buf);
    }

    static std::string escape(const std::string &s) {
        std::string out;
        for (char c: s) {
            if (c == '\n') out += "\\n";
            else if (c == '|') out += '/';
            else out += c;
        }
        return out;
    }

    static std::string unescape(const std::string &s) {
        std::string out;
        for (size_t i=0;i<s.size();++i) {
            if (s[i] == '\\' && i+1 < s.size() && s[i+1] == 'n') { out += '\n'; ++i; }
            else out += s[i];
        }
        return out;
    }

    static void appendCurrent(const std::string &buyer, const std::string &details, int total) {
        appendWithDate(todayDate(), buyer, details, total);
    }

    static void appendWithDate(const std::string &date, const std::string &buyer, const std::string &details, int total) {
        std::ofstream out(LOGFILE, std::ios::app);
        if (!out.is_open()) return;
        out << date << '|' << buyer << '|' << total << '|' << escape(details) << '\n';
        out.close();
    }

    static std::vector<SalesEntry> readAll() {
        std::vector<SalesEntry> res;
        std::ifstream in(LOGFILE);
        if (!in.is_open()) return res;
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            std::string date, buyer, totstr, det;
            size_t p1 = line.find('|');
            if (p1 == std::string::npos) continue;
            date = line.substr(0,p1);
            size_t p2 = line.find('|', p1+1); if (p2==std::string::npos) continue;
            buyer = line.substr(p1+1, p2-p1-1);
            size_t p3 = line.find('|', p2+1); if (p3==std::string::npos) continue;
            totstr = line.substr(p2+1, p3-p2-1);
            det = line.substr(p3+1);
            SalesEntry e; e.date = date; e.buyer = buyer; e.total = atoi(totstr.c_str()); e.details = unescape(det);
            res.push_back(e);
        }
        in.close();
        return res;
    }

    static int sumAll() {
        int s=0;
        auto v = readAll();
        for (auto &e: v) s += e.total;
        return s;
    }

    static std::vector<SalesEntry> filterByDate(const std::string &date) {
        std::vector<SalesEntry> out;
        auto v = readAll();
        for (auto &e: v) if (e.date == date) out.push_back(e);
        return out;
    }

    static void rewriteAll(const std::vector<SalesEntry> &v) {
        std::ofstream out(LOGFILE, std::ios::trunc);
        for (auto &e: v) out << e.date << '|' << e.buyer << '|' << e.total << '|' << escape(e.details) << '\n';
        out.close();
    }

    static int daysBetween(const std::string &a, const std::string &b) {
        // parse YYYY-MM-DD
        auto parse = [](const std::string &s)->std::tm {
            std::tm tm{};
            if (s.size() >= 10) {
                tm.tm_year = std::stoi(s.substr(0,4)) - 1900;
                tm.tm_mon = std::stoi(s.substr(5,2)) - 1;
                tm.tm_mday = std::stoi(s.substr(8,2));
            }
            return tm;
        };
        std::tm ta = parse(a); std::tm tb = parse(b);
        std::time_t ta_t = std::mktime(&ta);
        std::time_t tb_t = std::mktime(&tb);
        if (ta_t== (std::time_t)-1 || tb_t== (std::time_t)-1) return 0;
        double diff = std::difftime(tb_t, ta_t);
        return int(diff / (60*60*24));
    }

    static void pruneOlderThan(int days = 40) {
        auto all = readAll();
        std::string today = todayDate();
        std::vector<SalesEntry> keep;
        for (auto &e: all) {
            int d = daysBetween(e.date, today);
            if (d <= days) keep.push_back(e);
        }
        rewriteAll(keep);
    }

    static void printEntry(const SalesEntry &e) {
        cout << "[" << e.date << "] " << e.buyer << " - Rp " << e.total << "\n";
        cout << e.details << "\n";
        cout << "-------------------------\n";
    }

    static void interactiveMenu() {
        int p;
        do {
            cout << "\n===== CATATAN PENJUALAN =====\n";
            cout << "1. Lihat semua transaksi\n";
            cout << "2. Jumlahkan seluruh pendapatan\n";
            cout << "3. Cari transaksi per tanggal (YYYY-MM-DD)\n";
            cout << "4. Hapus catatan lebih dari 40 hari\n";
            cout << "0. Kembali\n";
            cout << "Pilih: "; cin >> p;
            if (p == 1) {
                auto v = readAll();
                for (auto &e: v) printEntry(e);
            } else if (p == 2) {
                int s = sumAll();
                cout << "Total pendapatan: Rp " << s << "\n";
            } else if (p == 3) {
                string date; cout << "Masukkan tanggal (YYYY-MM-DD): "; cin >> date;
                auto v = filterByDate(date);
                int sum=0; for (auto &e: v) { printEntry(e); sum += e.total; }
                cout << "Total pada " << date << ": Rp " << sum << "\n";
            } else if (p == 4) {
                pruneOlderThan(40);
                cout << "Prune selesai. Catatan >40 hari dihapus.\n";
            }
        } while (p != 0);
    }
}

#endif
