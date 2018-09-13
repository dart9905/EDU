#define ASSERT_STACK( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_LIST========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n=============================\n\n");\
\
fclose(files);\
assert (expression);\
}

#define DUMP //Dump ()

template <typename data_T>
class cell_t {
public:
    cell_t (data_T arg = 0) :
    _data (arg),
    _next (nullptr),
    _prev (nullptr)
    {};
    cell_t (const cell_t& that) = default;
    cell_t (cell_t&& that) {
        _data = std::move(that._data);
    }
    ~cell_t () {};
    
    data_T _data;
    cell_t* _next;
    cell_t* _prev;
};



template <typename data_T>
class list {
public:
    
    list (data_T arg = NULL);
    list (const list& that)  = default;
    list (list&& that) {
       _cell = std::move(that._cell);
    }
    ~list ();
    
    
    int  _size;
    cell_t<data_T>* _cell;
    cell_t<data_T>* _position_cell;
    cell_t<data_T>* _end;
    
    int addbe (cell_t<data_T>* cellbe, data_T arg);
    int addaf (cell_t<data_T>* cellaf, data_T arg);
    bool    Dump   ();
    bool    Dump   (char* name);
    void    Clear ();
    
private:
    char* _LOG_FILES_NAME = "LogFilesList.txt";
    
};



template <typename data_T>
list <data_T> :: list (data_T arg) :
_size (1),
_cell (new cell_t<data_T>)
{
    _position_cell = _cell;
    _end = _cell;
    ASSERT_STACK(_cell)
};



template <typename data_T>
list <data_T> :: ~list ()
{
    _cell = _position_cell;
    for (int i = 0; i < _size; i++) {
        _position_cell = _cell;
        if (i < _size)
            _cell = _cell->_next;
        delete _position_cell;
    }
};



template <typename data_T>
void list <data_T> :: Clear () {
    _cell = _position_cell->_next;
    cell_t<data_T>* cell;
    
    for (int i = 1; i < _size; i++) {
        cell = _cell;
        if (_cell != nullptr)
            _cell = _cell->_next;
        delete cell;
    }
    _position_cell->_next = nullptr;
    _position_cell->_data = NULL;
    _cell = _position_cell;
    _end = _position_cell;
    _size = 1;
}



//после
template <typename data_T>
int list <data_T> :: addbe (cell_t<data_T>* cellbe, data_T arg) {
    ASSERT_STACK(cellbe)
    
    cell_t<data_T>* new_cell = new cell_t<data_T>;
    if (new_cell == NULL)
        ASSERT_STACK(new_cell);
    
    _size++;
    new_cell->_data = arg;
    new_cell->_prev = cellbe;
    new_cell->_next = cellbe->_next;
    
    (new_cell->_prev)->_next = new_cell;
    if (new_cell->_next != NULL)
        (new_cell->_next)->_prev = new_cell;
    else
        _end = new_cell;
    
    
    return 0;
}



//перед
template <typename data_T>
int list <data_T> :: addaf (cell_t<data_T>* cellaf, data_T arg) {
    ASSERT_STACK(cellaf)
    
    cell_t<data_T>* new_cell = new cell_t<data_T>;
    if (new_cell == NULL)
        ASSERT_STACK(new_cell);
    
    _size++;
    new_cell->_data = arg;
    new_cell->_prev = cellaf->_prev;
    new_cell->_next = cellaf;
    
    if (new_cell->_prev != NULL)
        (new_cell->_prev)->_next = new_cell;
    else
        _position_cell = new_cell;
    
    return 0;
}


template <typename data_T>
bool list <data_T> :: Dump ()
{
    FILE *files = fopen (_LOG_FILES_NAME, "at");
    assert(files);
    
    fprintf(files, "==========list==========\n\n");
    
    
    fprintf (files, "_size = %i\n\n", _size);
    fprintf (files, "_position_cell = %i\n\n", _position_cell);
    _cell = _position_cell;
    for (int i = 0; i < _size; i++) {
        fprintf(files, "_data[%i] = %i\n", i, _cell->_data);
        _cell = _cell->_next;
    }
    
    fprintf(files, "\n===========================\n\n");
    
    fclose(files);
    return 0;
}



template <typename data_T>
bool list <data_T> :: Dump (char* name)
{
    FILE *files = fopen (name, "at");
    assert(files);
    
    fprintf(files, "==========list==========\n\n");
    
    
    fprintf (files, "_size = %i\n\n", _size);
    fprintf (files, "_position_cell = %i\n\n", _position_cell);
    _cell = _position_cell;
    for (int i = 0; i < _size; i++) {
        fprintf(files, "_data[%i] = %s\n", i, _cell->_data);
        _cell = _cell->_next;
    }
    
    fprintf(files, "\n===========================\n\n");
    
    fclose(files);
    return 0;
}


#undef DUMP
#undef ASSERT_STACK
