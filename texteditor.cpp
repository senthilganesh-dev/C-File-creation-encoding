#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <utility>


#include "huffman_coding.h"
namespace fs = std::filesystem;
using namespace std;

class file_manager {
public:
    bool is_closed;
    inline static string path_controller = "/home/senthil/c++/";
    file_manager() : is_closed(false) {}

    void index() {
        
        folder_controller();
        int ch = 0;
        cout << "\n1.Open 2.Create 3.Edit 4.Save as 5.Delete 6.Close\nEnter choice: ";
        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        if (ch == 1 || ch == 3) {
            display();
            cout << "Enter the file name with extension: ";
            string file_name;
            cin >> file_name;

            if (open(file_name)) {
                edit(file_name);
            } else {
                cout << "File Not Found.\n";
            }
        }
        else if (ch == 2) {
            auto [is_create, file] = create();
            if (is_create) {
                cout << "File created successfully.\n";
                edit(file);
            } else {
                cout << "Failed to create file.\n";
            }
        }
        else if (ch == 4) {
            if (save_as())
                cout << "File saved successfully.\n";
            else
                cout << "File not saved.\n";
        }
        else if (ch == 5) {
            display();
            string name;
            cout << "Enter file name with extension: ";
            cin >> name;
            if (open(name)) {
                fs::remove(path_controller + name); 
                cout << "Deleted " << name << endl;
                return;
            }
            cout << "Not found\n";
        }
        else if (ch == 6) {
            Close();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    void display() {
        error_code ec;
        for (const auto &dic : fs::directory_iterator(path_controller)) {
            string file = dic.path().filename().string();
            auto [size, ec] = size_of_file(file);
            if (!ec) {
                if (size < 1024)
                    cout << file << ':' << size << "B" << endl;
                else if (size < 1024 * 1024)
                    cout << file << ':' << size / 1024 << "KB" << endl;
                else
                    cout << file << ':' << size / (1024 * 1024) << "MB" << endl;
            }
            else {
                cout << file << ':' << "Folder" << endl;
            }
        }
    }

    void folder_controller() {
        display();
        cout << "1.Create \n2.Go to\n3.Skip\nChoice: ";
        int ch;
        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (ch == 1) {
            auto [is_created, newpath] = create_folder();
            if (is_created) {
                cout << "Folder created\n";
                
                path_controller = "/home/senthil/c++/" + newpath + "/";
            } else {
                cout << "Folder not created\n";
            }
        }
        else if (ch == 2) {
            go_to_folder();
        }
    }
    
    pair<bool, string> create_folder() {
        string folder_name;
        cout << "Folder name: ";
        cin >> folder_name;
        
        
        if (fs::create_directories(path_controller + folder_name)) {
            cout << folder_name << " is created\n";
            return {true, folder_name};
        }
        return {false, folder_name};
    }

    void go_to_folder() {
        string gopath;
        cout << "Enter the folder name: ";
        cin >> gopath;

        
        path_controller = "/home/senthil/c++/" + gopath + "/";
    }

    bool open(const string &name) {
       
        ifstream file(path_controller + name);
        return file.is_open();
    }

    void edit(const string &name) {
        try{
       if(name == "\n") return;
        ifstream readFile(path_controller + name);
        if (readFile.is_open()) {
            cout << "\n--- Current Content ---\n";
            string line;
            while (getline(readFile, line)) {
                cout << line << "\n";
            }
            cout << "-----------------------\n";
            readFile.close();
        }
        
    }
    catch(...){
        cout<<"Not done.."<<endl;
    }
        ofstream file(path_controller + name, ios::app);
        if (!file.is_open()) {
            cout << "Error opening file for appending.\n";
            return;
        }

        cout << "Enter text to append: ";
        cin.ignore(10000, '\n');
        string text;
        getline(cin, text);
        try{
        for(auto [x,y]: encrypt(text)){
            file<< x<< " : " <<y<<"   ";
        }
    }
    catch(...){
        cout<<"Not Done\n";
        return;
    }
        if (save(file))
            cout << "Saved successfully.\n";
        else
            cout << "Error saving file.\n";

        file.close();
    }

    bool save(ofstream &file) {
        return (file.is_open() && file.good());
    }

    pair<bool, string> create() {
        cout << "Enter file name with extension: ";
        string file_name;
        cin.ignore(1000,'\n');
        cin >> file_name;

        ofstream file(path_controller + file_name, ios::out);
        bool success = file.is_open();
        return {success, file_name};
    }

    bool save_as() {
        cout << "Enter source file name: ";
        string source;
        cin.ignore(1000,'\n');
        cin >> source;

        if (!open(source)) {
            cout << "Source file does not exist.\n";
            return false;
        }

        cout << "Enter the new file name: ";
        string destination;
        cin.ignore(1000,'\n');
        cin >> destination;

        std::error_code ec;
        fs::copy_file(path_controller + source, path_controller + destination, fs::copy_options::overwrite_existing, ec);
        fs::remove(path_controller + source);

        return !ec;
    }

    pair<uintmax_t, bool> size_of_file(string file) { 
        error_code ec;
       
        uintmax_t size = fs::file_size(path_controller + file, ec); 
        return {size, static_cast<bool>(ec)};
    }

    void Close() {
        is_closed = true;
        
        cout << "Closing file manager...\n";
    }
};

int main() {
    file_manager fm;

    do {
        fm.index();
    } while (!fm.is_closed);

    return 0;
}