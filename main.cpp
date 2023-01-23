#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

#define A 192
#define uA 208144

void replace(std::vector<unsigned char> &v, unsigned char c, unsigned char r){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == c) {
            v[i] = r;
            continue;
        }
        if(v[i] == r){
            v[i] = c;
            continue;
        }
    }
}

unsigned char d(char * s){
    return (s[0] * 1000 + s[1]) - uA + A;
}

void pr(std::vector<unsigned char> v){
    std::cout << std::endl;
    for(int i = 0; i < v.size(); i++) {
        if(i % 5 == 0) std::cout << " ";
        std::cout << v[i];
    }
    std::cout << std::endl;
}

std::vector<int> analyz(std::vector<unsigned char> v, bool printer) {
    std::cout << std::endl;
    std::cout << "Symbols analysis" << std::endl;
    std::cout << std::endl;
    std::vector<int> counter(32);
    for(int i = 0; i < v.size(); i++){
        counter[v.at(i) - A]++;
    }
    if(printer) {
        for (int i = 0; i < counter.size(); i++) {
            std::cout << (char) (i + 192) << " = " << counter.at(i) << (counter.at(i) < 10 ? "  | " : " | ");
            for (int j = 0; j < counter.at(i); j++) std::cout << "-";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return counter;
}

std::map<std::string, int> nAnalyz(std::vector<unsigned char> v, int count, bool printer){
    std::map<std::string, int> r;
    for(auto i = v.begin(); i != v.end(); i++){
        char *ch = new char[count];
        std::copy(i, i + count, ch);
        std::string temp(ch);
        temp.resize(count);
        auto iter = r.find(temp);
        if(iter == r.end()){
            r.insert({temp, 1});
        } else {
            (iter->second)++;
        }
    }

    for(auto iter = r.begin(); iter != r.end();){
        if(!(count == 2 && iter->first.at(0) == iter->first.at(1))
                    && iter->second == 1) iter = r.erase(iter);
        else iter++;
    }

    if(printer) {
        std::cout << std::endl;
        std::cout << "Analysis " << count << "-gramm" << std::endl;
        for(auto i : r){
            std::cout << i.first << " = " << i.second << (i.second < 10 ? "  | ": " | ");
            for(int c = 0; c < i.second; c++) std::cout << "-";
            std::cout << std::endl;
        }
    }

    return r;
}

std::vector<unsigned char> decoder(std::string input){
    std::vector<unsigned char> decoding;
    for(int i = 0; i < input.size(); i++){
        int32_t symb = (unsigned char)input.at(i);
        if(symb != 208){
            continue;
        }
        i++;
        symb *= 1000;
        symb += (unsigned char)input.at(i);
        unsigned char decSymb = (char)(symb - uA) + 192;
        decoding.push_back(decSymb);
    }
    return decoding;
}

int main() {
    setlocale(LC_ALL,"Russian");

    std::string input = "ФСЩРЫ МПЫМЦ ЧФСБМ НЩЧБЪ ЧЩТФФ ЭМПМЬ ДЪСЧМ\n"
                        "ЪДФЪЧ ТФСДЪ МБЗЧЪ ЪЙЖРЯ ТЪЭЮР ЕЖРСЩ ДНРЮР\n"
                        "МЪЪМФ ЛРСДЧ СФЕЫМ ПМЖБЧ СЩДРЗ РБМКН ТГДЧП\n"
                        "МЬМЛР СДЗРР ЭДЭРФ СЩЧЫР СЧЗЕБ ФЕЛЧФ ЭРГКЗ\n"
                        "МНЧЕЪ РОЩДК ЩТИРС ЧЗЕКЗ МТЖЙИ ЗЧЪРО";

    std::vector<unsigned char> decoding;

    std::vector<int> counter(32);

    std::string chast = "ОЕАИНТСРВЛКМДПУЯЫЬГЗБЧЙХЖШЮЦЩЭФЪ";
    std::vector<unsigned char> decChast;

    decoding = decoder(input);
    decChast = decoder(chast);

    pr(decoding);

    analyz(decoding, 1);
    nAnalyz(decoding, 2, true);
    nAnalyz(decoding, 3, true);

    replace(decoding, d("Ъ"), d("Н"));
    replace(decoding, d("М"), d("О"));
    replace(decoding, d("Р"), d("И"));
    replace(decoding, d("Ю"), d("Ц"));

    replace(decoding, d("П"), d("В"));
    replace(decoding, d("С"), d("Т"));
    replace(decoding, d("Д"), d("А"));
    replace(decoding, d("Щ"), d("Р"));
    replace(decoding, d("Ъ"), d("Д"));
    replace(decoding, d("Ф"), d("С"));
    replace(decoding, d("Ы"), d("Б"));
    replace(decoding, d("В"), d("Г"));
    replace(decoding, d("Ю"), d("Ж"));
    replace(decoding, d("Ч"), d("Е"));
    replace(decoding, d("Ы"), d("В"));
    replace(decoding, d("Ф"), d("У"));
    replace(decoding, d("Э"), d("К"));
    replace(decoding, d("Ь"), d("П"));
    replace(decoding, d("З"), d("Л"));
    replace(decoding, d("Й"), d("Ы"));
    replace(decoding, d("Ю"), d("М"));
    replace(decoding, d("Я"), d("Ф"));
    replace(decoding, d("Ч"), d("Я"));
    replace(decoding, d("З"), d("Ч"));
    replace(decoding, d("Э"), d("З"));
    replace(decoding, d("Й"), d("Х"));
    replace(decoding, d("Ю"), d("Й"));
    replace(decoding, d("Щ"), d("Ш"));

    std::cout << "-------------------------" << std::endl;

    analyz(decoding, 1);
    nAnalyz(decoding, 2, true);
    nAnalyz(decoding, 3, true);
    pr(decoding);

    system("pause");
    return 0;
}
