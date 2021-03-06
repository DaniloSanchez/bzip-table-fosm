// tag file
class TagFileEntry
{
public:
  long int id;
  string key;
  string value;
  //const char * key;
  //const char * value;
public:
  TagFileEntry(const long int & id,const string & k,const string & v ):
    id(id),
    key(k),
    value(v)  {      }
  void write (ostream & os) {
    os << id  << "\t" 
        << key << "\t" 
        << value  <<  endl;
  }

};

 
class TagFile {
public:
  vector< TagFileEntry > data;
  ofstream  txtfile;
  string    filename;
  long long total_count;
  const char * dirname;
  long blockcount;
  
  TagFile(const char * dirname,long blockcount,const char * filename)
    :total_count(0),
     filename(filename),
     dirname(dirname),
     blockcount(blockcount)
  {    
    string outputbase(string (dirname) + string(filename));
    txtfile.open(string(outputbase+ ".txt").c_str());    

  }           

  ~TagFile()
  {
    int count =data.size();
    write(count);
    txtfile.close();
    cout << "Closing file " << dirname << filename << ", wrote " << total_count << endl;
  }

  void flush()
  {
    write(data.size());
  }

  long long count()
  {
    return total_count;
  }

  void write(int count)
  {
    // append the data to the file
    // file.write((const char*)&data[0], count * sizeof(T)); // skip the binary file now
    vector< TagFileEntry >::iterator i;
    for(i=data.begin();i!=data.end();i++)
      {
        i->write (txtfile);
      }
    data.clear(); // erase the data
  }
  
  void push_back (long int pos, const string & key, const string & val){
    total_count++;
    //cerr << "tag:"<< key << " = "<< val << endl;
    TagFileEntry v (pos,key,val);
    data.push_back(v);
    int count =data.size();
    if (count > 100)   {
      //cerr << "wrote tags count " << total_count << endl;
      write(count);
    }           
  }
       
};
