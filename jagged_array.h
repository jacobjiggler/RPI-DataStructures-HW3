    //  File: jagged_array.h
    // Purpose: Header for declaration of jagged array class and associated functions.
    
    //to do
    
    
    //readme.txt
    //documentation
    #ifndef __jagged_array_h_
    #define __jagged_array_h_
    
    using namespace std;
    
    // jagged_array
    
    template <class T> class JaggedArray {
    
    public:
      // TYPEDEFS
      typedef T* iterator;
      typedef const T* const_iterator;
      typedef unsigned int size_type;
    
      // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
      JaggedArray(size_type n) { this->create(n); }
      JaggedArray(const JaggedArray& v) { copy(v); }
     
    
      // MEMBER FUNCTIONS AND OTHER OPERATORS
      T& operator[] (size_type i) { return m_data[i]; }
      const T& operator[] (size_type i) const { return m_data[i]; }
      void clear();
      void print();
      void addElement(size_type i, const T& val);
      T getElement(size_type w, size_type e);
      void removeElement(size_type a, size_type b);
      size_type numBins() const { return m_size; }
      size_type numElements() const { return m_innersize;}
      size_type numElementsInBin(size_type l);
      ~JaggedArray();
      bool isPacked() {return isalreadypacked == 1;}
      void pack();
      void unpack();
    
    private:
      // PRIVATE MEMBER FUNCTIONS
      void create();
      void create(size_type numbins);
      void copy(const JaggedArray<T>& v);
    
      // REPRESENTATION
      T** m_data;
      size_type m_size;  // Number of elements stored in the vector
      size_type m_innersize; //Total number of elements in all bins
      size_type * counts; //holds the elements in each bin
      T* packed_values;
    size_type* offsets;
      size_type isalreadypacked;
    };
    
    
    
    // Create a vector with size n, each location having the given value
    template <class T> void JaggedArray<T>::create(size_type numbins) {
         
        m_data = new T*[numbins];
    
      counts = new size_type[numbins];
      for(size_type i = 0; i < numbins; i++){
        m_data[i] = new T[0];
        counts[i] = 0;
      }
      m_size = numbins;
      m_innersize = 0;
      isalreadypacked = 0;
      
      packed_values = NULL;
      offsets = NULL;
    }
    
    
    
    
    // Create the vector as a copy of the given vector.
    template <class T> void JaggedArray<T>::copy(const JaggedArray<T>& v) {
    this->m_size = v.m_size;
      this->m_innersize = v.m_innersize;
      this->isalreadypacked = v.isalreadypacked;
    if (isPacked()){
    for (size_type i = 0; i < m_size; i++){
    delete [] m_data[i];
    }
      delete [] m_data; 
     this->m_data = new T*[this->m_size];
      delete [] counts;
      this->counts = new size_type[v.m_size];
      for (int i = 0; i < v.m_size; i++)
          this->counts[i] = v.counts[i];
      // Copy the data
      for (size_type i = 0; i < m_size; ++i){
           for (size_type p = 0; p < counts[i]; ++p){
                 this -> m_data[i][p] = v.m_data[i][p];
        }
           }
           } 
    else {
        //delete [] packed_values
        //delete [] packed_values
    for (int i = 0; i < m_innersize; i++){
    packed_values[i] = v.packed_values[i];
    }
    for (int i = 0; i < m_size; i++){
    offsets[i] = v.offsets[i];
        
    }
    }
      
      
     
      
      
     
           }
    
    // Add an element to the end, resize if necesssary.
    template <class T> void JaggedArray<T>::addElement(size_type i, const T& val) {
    if (i < 0 || i > m_size - 1){
    cerr << " error: bind index out of bounds";
        exit(1);
    }
    if (isPacked()){
    cerr << "its packed, you cant get anything " << endl;
    exit(1);
    }
        // Allocate a larger array, and copy the old values
    
        // Allocate and copy the old array
        T* new_datatemp = new T[counts[i] + 1];
        for (size_type a=0; a<counts[i]; ++a)
          new_datatemp[a] = m_data[i][a];
         new_datatemp[counts[i]] = val;
        // Delete the old array and reset the pointers
        delete [] m_data[i];
        m_data[i] = new_datatemp;
      counts[i] = counts[i] + 1;
    
      // Add the value at the last location and increment the bound
    
      ++m_innersize;
    }
    
    // Shift each entry of the array after the iterator. Return the iterator,
    // which will have the same value, but point to a different location.
    template <class T> void JaggedArray<T>::removeElement(size_type a, size_type b) {
    if (a < 0 || a > m_size - 1 || a < 0 || b > counts[a]){
    cerr << " error: bind index out of bounds";
        exit(1);
    }
    if (isPacked()){
    cerr << "its packed, you cant change anything " << endl;
    exit(1);
    }
     T* new_datatemp = new T[counts[a] - 1];
    for (size_type q = 0; q < b; q++)
        new_datatemp[q] = m_data[a][q];
    
     for (size_type q = b; q < counts[a] - 1; ++q)
        new_datatemp[a] = m_data[a][q+1];
    
     delete [] m_data[a];
    m_data[a] = new_datatemp;
    
      counts[a] = counts[a] - 1;
      m_innersize--;
    }
    
    template <class T> T JaggedArray<T>::getElement(size_type w, size_type e){
    if (w < 0 || w > m_size - 1 || e < 0){
    cerr << " error: bind index out of bounds" << endl;
        exit(1);
    }
    if (!isPacked()){
    if (w > m_size - 1 || w < 0){
    cerr << "error: index of bin array w out of bounds" << endl;
    exit(1);
    
    }
    if (e > counts[w] - 1 || e < 0){
    cerr << "error: index of array e out of bounds" << endl;
    exit(1);
    
    }
    return m_data[w][e];
    
    }
    else {
    if (w != m_size - 1){
    
    return packed_values[offsets[w] + e] ;
    }
    else {
    
    return packed_values[offsets[w] + e];
    }
    }
    }
    
    template <class T> void JaggedArray<T>::print(){
    if (!isPacked()){
    cout << "unpacked ";
    cout << "JaggedArray" << endl;
    cout << "  num_bins: " << m_size << endl;
    cout << "  num_elements: " << m_innersize << endl;
    cout << "  counts:  ";
    size_type max = 0;
    for (size_type u = 0; u < m_size; u++){
        cout << counts[u] << " ";
        if (counts[u] > max){
            max = counts[u];
        }
    }
    cout << endl;
    cout << "  values:  ";
    for (size_type o = 0; o < max; o++){
        if (o > 0)
            cout << "           ";
    for (size_type u = 0; u < m_size; u++){
    if (counts[u] > o ){
    cout << m_data[u][o];
    }
    else {
        cout << " ";
    }
    cout << " ";
    }
    cout << endl;
    }
    }
    else {
        cout << "packed ";
        cout << "JaggedArray" << endl;
    cout << "  num_bins: " << m_size << endl;
    cout << "  num_elements: " << m_innersize << endl;
    cout << "  offsets:  ";
    for (size_type u = 0; u < m_size; u++){
        cout << offsets[u] << " ";
    }
    cout << endl;
    cout << "  values:   ";
    for (size_type u = 0; u < m_innersize; u++){
    cout << packed_values[u];
    cout << " ";
    }
    cout << endl;
    }
    
    cout << endl;
    }
    
    template <class T> void JaggedArray<T>::pack() {
		delete [] packed_values;
		delete [] offsets;
         if (isPacked()){
    cerr << "Stop trying to pack an already packed jaggedarray " << endl;
    exit(1);
    }
    packed_values = new T[m_innersize];
    offsets = new size_type[m_size];
    size_type total = 0;
    offsets[0] = 0;
    for (size_type u = 1; u < m_size; u++){
        total = total + counts[u - 1];
        offsets[u] = total;
    }
    
    size_type temp = 0;
    for (size_type s = 0; s < m_size; s++){
    for (size_type o = 0; o < counts[s]; o++){
    packed_values[temp] = m_data[s][o];
    temp++;
    }
    }
    delete [] counts;
    for (size_type i = 0; i < m_size; i++)
    delete [] m_data[i];
    delete [] m_data;
    counts = NULL;
    m_data = NULL;
    
    isalreadypacked = 1;
    }
    
    template <class T> void JaggedArray<T>::unpack() {
     if (!isPacked()){
    cerr << "Stop trying to unpack an already unpacked jaggedarray " << endl;
    exit(1);
    }
    
     delete [] m_data;
    delete [] counts;
     counts = new size_type[m_size];
     for (size_type k = 0; k < m_size - 1; k++){
     counts[k] = (offsets[k+1] - offsets[k]);
    
     }
    counts[m_size - 1] = m_innersize - offsets[m_size - 1];
    
    size_type total = 0;
    size_type a = 0;
    m_data = new T*[m_size];
    T* tempi;
    for (size_type j = 0; j < m_size; j++){
        tempi = new T[counts[j]];
        a = 0;
    for (size_type n = 0; n < counts[j]; n++){
    tempi[n] = packed_values[n + total];
    a++;
    }
     total = total + a;
    m_data[j] = tempi;
    }
    delete [] packed_values;
        delete [] offsets;
     packed_values = NULL;
    offsets = NULL;
     isalreadypacked = 0;
    
    }
    
      template <class T> unsigned int JaggedArray<T>::numElementsInBin(size_type l) {
     if (l < 0 || l > m_size - 1){
    cerr << " error: bind index out of bounds";
        exit(1);
    }
       if(!isPacked()){
      return counts[l];
       }
      else {
    
    
      if (l == m_size - 1){
     return m_innersize - offsets[l];
      }
      else{
     return (offsets[l+1] - offsets[l]);
      }
    
    
     }
      }
    
     template <class T> void JaggedArray<T>::clear() {
    delete [] counts;
    counts = new size_type[m_size];
     for (size_type a = 0; a < m_size; a++){
       
        T* new_a = new T[0];
        delete [] m_data[a];
        m_data[a] = new_a;
    
        counts[a] = 0;
     }
    m_innersize = 0;
    
     }
    
    template <class T> JaggedArray<T>::~JaggedArray() {
    for (size_type i = 0; i < m_size; i++){
    delete [] m_data[i];
    }
    delete [] counts;
    delete [] m_data; 
    delete [] packed_values;
    delete [] offsets;
    
     }
    #endif
