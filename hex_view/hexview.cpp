#include <iostream>
#include <fstream>
#include <experimental/filesystem> 
#include <iterator>
#include <sstream>
#include <bitset>

using namespace std;
using namespace std::experimental::filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Missing filename\n";
        return EXIT_FAILURE;
    }

    
    path current_file(argv[0]);
    cout << "Current: " << current_file.string() << endl;

    path file(argv[1]);
    
    if (!file.is_absolute()) {
        path temp = current_file;
        temp.remove_filename();
        file = current_path() / file;
    }
    
    
    
    if (!exists(file)) {
        cout << "Can't open: " << file.string() << endl;
        return EXIT_FAILURE;
    }

    ifstream is(file.string());
    istream_iterator<uint8_t> start(is), end;
    std::vector<uint8_t> data(start, end);
    std::cout << "Read " << data.size() << " bytes" << std::endl;

    stringstream bin_str;
    for (auto i = 0u; data.size() != i; ++i) 
    {
        cout << std::hex << (int)data[i] << std::dec << " ";
        bin_str << std::bitset< 8 >(data[i]) << " ";

        if (0 != i && (i+1) % 4 == 0) {
            cout    << "  ";
            bin_str << " ";
        }
        if (0 != i && (i+1) % (4*2) == 0) {
            cout << bin_str.str();
            cout << "\n";
            bin_str.swap(stringstream{});
        }
    }
    cout << bin_str.str() << endl;

    

    return 0;
}

