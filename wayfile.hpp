//class WayNodeFile
class WayNodeFileEntry
{
public:
  //  long int way;
  //  long int node;
  int iway;
  int inode;
public:
  WayNodeFileEntry(//const long int & way,
                   const int & iway,
                   //const long int & node,
                   const int & inode):
    //    way(way),
    //    node(node),
    iway(iway),
    inode(inode)
  {      
  }

  void write (ostream & os) {
    //    os << way  << "[" << iway << "]\t" 
    //       << node << "[" << inode << "]\t" << endl;
    os <<  iway <<"\t" 
       <<  inode << endl;
  }

};


class WayNodeFile {
public:
  vector< WayNodeFileEntry > way_nodes;
  ofstream txtfile;
  ofstream txtfile2; // debug of the bin file
  ofstream file;
  string   filename;
  long int total_count;
  long int write_count;
  int total_way_count;
  
  WayNodeFile(const char * filename)
    :txtfile(string(string ("datafiles/") +  string(filename) + ".txt").c_str()),
     txtfile2(string(string ("datafiles/") +  string(filename) + "2.txt").c_str()),
     file(string(string ("datafiles/") + string(filename) + ".bin").c_str()),
     total_way_count(0),
     total_count(0),
     write_count(0),
     filename(filename)
  {    
  }           

  ~WayNodeFile()
  {
    int count =way_nodes.size();
    write(count);
    way_nodes.clear();
    txtfile.close();
    txtfile2.close();
    cout << "Closing file " << filename << ", wrote " << total_count << endl;
  }

  void flush()
  {
    write(way_nodes.size());
  }

  long long count()
  {
    return total_count;
  }

  void write(int count)
  {
    vector< WayNodeFileEntry >::iterator i;
    int index=0;
    int way=-1;
    for(i=way_nodes.begin();i!=way_nodes.end();i++)
      {
        if (way != i->iway)
          {
            long int zero=-1;
            file.write((const char*)&zero, 1 * sizeof(int)); // zero before each list
            txtfile2 << "Z" << zero << endl;

            // new way
            file.write((const char*)&i->iway, 1 * sizeof(int)); // skip the binary file now
            way = i->iway; // we look for changes
            txtfile2 << "W:"<< way<< endl; // way
            total_way_count++;
          }

        // write the node referenced in this way as a long 
        file.write((const char*)&(i->inode), 1 * sizeof(int));
        txtfile2 << "ND:"<< i->inode; // way

        i->write (txtfile);
        write_count++;
        index ++;

      }
    cout << "wrote " << total_count << endl;
    way_nodes.clear(); // erase the way_nodes
  }
  
  void push_back (int & iway,int & inode ){
    total_count++;
    WayNodeFileEntry v (iway,inode);
    way_nodes.push_back(v);
    int count =way_nodes.size();
    if (count > blocksize)   {
      write(count);
    }           
  }
       
};
