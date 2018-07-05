//
//  main.cpp
//  project1
//
//  Created by yuqiao liang on 2/24/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <stdexcept>


using namespace std;
const char* hex_to_bin(char c);
string bin_to_symbol(string bin_str, int addr);
string get_register(string bin_in,int address);
string process_name(string const& s);
int signed_conversion(string raw_bin);
string convert_to_hex(int to_convert);
bool found_the_address(string first,list<string> address_list);
    bool error = false;
list<string> address_list;



int main( int argc,  char *argv[])
{
    map<string, string> command_map;
    
    string address_to_insert;
    string input_str;
    ifstream file_in(argv[1] ,std::ios::binary);
    ifstream file_in_check(argv[1] ,std::ios::binary);
   
    

    long int addr =0;
    int address = 0;
    
    if (argc == 1)
    {
        cout<<"no file is specified"<<endl;
        exit(EXIT_FAILURE);
    }
    
    if ( !file_in )
    {
        cout << "the specified file cannot be opened"<<endl;
        exit(EXIT_FAILURE);
    }
    addr = 0;
    
    

    
    while((file_in_check >> input_str).good())
    {

        try
        {
            if (input_str.length()!=8)
            {
                throw address;
            }
            
        } catch (int addr)
        {error = true;
            cout<<"line "<<address<<" doesn’t contain 8 hexadecimal digits"<<endl;
    }

        address+=1;

    }
    
    if (error == false)
    {

        addr= 0;
        address=0;
    string binary_output;
    while((file_in >> input_str).good())
    {

        binary_output ="";

    for(unsigned i = 0; i != input_str.length(); ++i)
    {
        binary_output += hex_to_bin(input_str[i]);
    }
        
        command_map.insert( pair<string, string >(convert_to_hex(addr),bin_to_symbol(binary_output,address) ));
        addr+= 0x4;
        address+=1;

    }
        if (error == false)
        {
     ofstream outFile(process_name(argv[1])+".s");
    for (map<string,string>::iterator it = command_map.begin();it!= command_map.end();++it  )
    {
        if (found_the_address(it->first, address_list))
        {
            outFile<<"Addr_"<<it->first<<":"<<endl;
           outFile<<"         "<<it->second<<endl;
        }
        else
                outFile<<"         "<<it->second<<endl;
    }
        }
    file_in.close ( );
     exit(EXIT_SUCCESS);
    }
    else
        exit(EXIT_FAILURE);
}

const char* hex_to_bin(char c)
{

    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "0000";
    }
}

string bin_to_symbol(string bin_str,int address)
{

    string symbol_result;
    string opcode = bin_str.substr(0,6);
    string rs = bin_str.substr(6,5);
    string rt = bin_str.substr(11,5);
    string rd = bin_str.substr(16,5);
    string shamt = bin_str.substr(21,5);
    string function_code = bin_str.substr(26,6);
    string immediate = bin_str.substr(16,16);
   
    if (opcode == "000000")
    {
        if (function_code == "100000")
        {
            symbol_result+="add ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "100001")
        {
            symbol_result+="addu ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "100100")
        {
            symbol_result+="and ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "001000")
        {
            symbol_result+="jr ";
            symbol_result+=get_register(rs,address);
        }
        else if (function_code == "100111")
        {
            symbol_result+="nor ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            
        }
        else if (function_code == "100101")
        {
            symbol_result+="or ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "101010")
        {
            symbol_result+="slt ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);

        }
        else if (function_code == "101011")
        {
            symbol_result+="sltu ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "000000")
        {
            symbol_result+="sll ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(shamt,nullptr,2));
            
        }
        else if (function_code == "000010")
        {
            symbol_result+="srl ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(shamt,nullptr,2));
        }
        else if (function_code == "100010")
        {
            symbol_result+="sub ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else if (function_code == "100011")
        {
            symbol_result+="subu ";
            symbol_result+=get_register(rd,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
        }
        else
        {
            cout<<function_code<<" cannot be dissassemable at line "<<address+1<<endl;
            error = true;
            exit(EXIT_FAILURE);
        }
    }
    else if (opcode =="001000")
        {
            symbol_result+="addi ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
        }
        else if (opcode =="001001")
        {
            symbol_result+="addiu ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(immediate,nullptr,2));
        }
        else if (opcode =="001100")
        {
            symbol_result+="andi ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
        }
        else if (opcode =="000100")
        {
            symbol_result+="beq ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+="Addr_";
            symbol_result+= convert_to_hex(((address+1+(signed_conversion(immediate)))*4));
            address_list.push_back(convert_to_hex(((address+1+(signed_conversion(immediate)))*4)));
        }
        else if (opcode =="000101")
        {
            symbol_result+="bne ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+="Addr_";
            symbol_result+= convert_to_hex(((address+1+(signed_conversion(immediate)))*4));
            address_list.push_back(convert_to_hex(((address+1+(signed_conversion(immediate)))*4)));
        }
        else if (opcode =="100100")
        {
            symbol_result+="lbu ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else if (opcode =="110000")
        {
            symbol_result+="ll ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else if (opcode =="001111")
        {
            symbol_result+="lui ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
        }
        else if (opcode =="100011")
        {
            symbol_result+="lw ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";

        }
        else if (opcode =="001101")
        {
            symbol_result+="ori ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(immediate,nullptr,2));
            
        }
        else if (opcode =="001010")
        {
            symbol_result+="slti ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            
        }
        else if (opcode =="001011")
        {
            symbol_result+="sltiu ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(immediate,nullptr,2));
        }
        else if (opcode =="001001")
        {
            symbol_result+="addiu ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=get_register(rs,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(immediate,nullptr,2));
        }
        else if (opcode =="101000")
        {
            symbol_result+="sb ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else if (opcode =="111000")
        {
            symbol_result+="sc ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else if (opcode =="101001")
        {
            symbol_result+="sh ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";

        }
        else if (opcode =="101011")
        {
            symbol_result+="sw ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(signed_conversion(immediate));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else if (opcode =="100101")
        {
            symbol_result+="lhu ";
            symbol_result+=get_register(rt,address);
            symbol_result+=", ";
            symbol_result+=to_string(stoi(immediate,nullptr,2));
            symbol_result+="(";
            symbol_result+=get_register(rs,address);
            symbol_result+=")";
        }
        else
        {
            cout<<bin_str<<" cannot be dissassemable at line "<<address+1<<endl;
            error = true;
            exit(EXIT_FAILURE);
        }
    
    return symbol_result;
}

string get_register(string bin_in,int address)
{
    if (bin_in == "00000")
    {
        return "$zero";
    }
    else if (bin_in == "00001")
    {
        return "$at";
    }
    else if (bin_in == "00010")
    {
        return "$v0";
    }
    else if (bin_in == "00011")
    {
        return "$v1";
    }
    else if (bin_in == "00100")
    {
        return "$a0";
    }
    else if (bin_in == "00101")
    {
        return "$a1";
    }
    else if (bin_in == "00110")
    {
        return "$a2";
    }
    else if (bin_in == "00111")
    {
        return "$a3";
    }
    else if (bin_in == "01000")
    {
        return "$t0";
    }
    else if (bin_in == "01001")
    {
        return "$t1";
    }
    else if (bin_in == "01010")
    {
        return "$t2";
    }
    else if (bin_in == "01011")
    {
        return "$t3";
    }
    else if (bin_in == "01100")
    {
        return "$t4";
    }
    else if (bin_in == "01101")
    {
        return "$t5";
    }
    else if (bin_in == "01110")
    {
        return "$t6";
    }
    else if (bin_in == "01111")
    {
        return "$t7";
    }
    else if (bin_in == "10000")
    {
        return "$s0";
    }
    else if (bin_in == "10001")
    {
        return "$s1";
    }
    else if (bin_in == "10010")
    {
        return "$s2";
    }
    else if (bin_in == "10011")
    {
        return "$s3";
    }
    else if (bin_in == "10100")
    {
        return "$s4";
    }
    else if (bin_in == "10101")
    {
        return "$s5";
    }
    else if (bin_in == "10110")
    {
        return "$s6";
    }
    else if (bin_in == "10111")
    {
        return "$s7";
    }
    else if (bin_in == "11000")
    {
        return "$t8";
    }
    else if (bin_in == "11001")
    {
        return "$t9";
    }
    else if (bin_in == "11010")
    {
        return "$k0";
    }
    else if (bin_in == "11011")
    {
        return "$k1";
    }
    else if (bin_in == "11100")
    {
        return "$gp";
    }
    else if (bin_in == "11101")
    {
        return "$sp";
    }
    else if (bin_in == "11110")
    {
        return "$fp";
    }
    else if (bin_in == "11111")
    {
        return "$ra";
    }
    else
    {
        cout <<"Cannot disassemble <"<< bin_in<<"> at line <"<<address+1<<"<"<<endl;
        error = true;
        exit(EXIT_FAILURE);
    }

}

int signed_conversion(string raw_bin)
{
    
    int bin_to_convert = stoi(raw_bin,nullptr,2);
    if (bin_to_convert>32767) {
        bin_to_convert = bin_to_convert-65536;
    }
    else
        bin_to_convert = bin_to_convert;
    return bin_to_convert;
}


string convert_to_hex(int to_convert)
{
    string result;
    stringstream ss;
    ss << setw(4)<< setfill('0') <<std::hex <<to_convert;
    ss >> result;
    return result;
}



bool found_the_address(string first,list<string> address_list)
{
    bool found = false;
    found = (find(address_list.begin(), address_list.end(), first) != address_list.end());
    return found;
}
string process_name(string const& s)
{
    string::size_type pos = s.find('.');
    if (pos != std::string::npos)
    {
        return s.substr(0, pos);
    }
    else
    {
        return s;
    }
}

