#ifndef __READ_OUTPUT_H__
#define __READ_OUTPUT_H__
#include<string>
#include<vector>
#include<map>
#include <filesystem>
#include<fstream>



class LookupTable{
    private:
    std::vector<std::filesystem::path> itop{};
    std::map<std::filesystem::path,int> ptoi{};
    int _size=0;
    public:
    LookupTable();
    bool is_in(std::filesystem::path &p){
        return ptoi.contains(p);
    }
    void insert(std::filesystem::path &p){
        if(!ptoi.contains(p)){
            itop.push_back(p);
            ptoi[p]=itop.size()-1;
        }
        _size++;
    }
    int get_idx(std::filesystem::path &p){
        return ptoi[p];
    }
    std::filesystem::path &get_path(int i){
        return itop[i];
    }
    int size(){
        return _size;
    }
};
class UnionFind{
    private:
    std::vector<int> parent{};
    public:
    int Find(int s){
        while (s!=parent[s]){
            s = parent[s];
        }
        return s;
    }
    void Union(int s, int t){
        int rs = Find(s),rt = Find(t);
        parent[rt]=rs;
    }
    void resize(int size){
        int former_size = parent.size();
        if(size>former_size){
            parent.resize(size);
            for(int i = former_size;i<size;i++)parent[i]=i;
        }
    }
    bool equal(int s,int t){
        return Find(s)==Find(t);
    }
    int size(){
        return parent.size();
    }
};
class ReadOutput
{
private:
    UnionFind _uf{};
    LookupTable _lookup{};
public:
    ReadOutput(std::filesystem::path &output_dir);
    LookupTable &lookup(){return _lookup;}
    UnionFind &unionfind(){return _uf;}
};

ReadOutput::ReadOutput(std::filesystem::path &output_dir){
    for(auto f : std::filesystem::directory_iterator(output_dir)){
        std::ifstream csv(f.path());
        std::string line;    
        while (std::getline(csv,line)){
            std::filesystem::path file1(line.substr(0,line.rfind(','))),file2(line.substr(line.rfind(',')+1,line.length()));
            _lookup.insert(file1);_lookup.insert(file2);
            _uf.resize(_lookup.size());
            if(f.path().filename()=="equal.csv"){
                int idx1=_lookup.get_idx(file1),idx2=_lookup.get_idx(file2);
                _uf.Union(idx1,idx2);
            }
        }    
    }
}

#endif