#include <container.h>


Container::Container() : _size(0), _capacity(1) {
    _data = new Figure*[_capacity];
}

Container::~Container(){
    delete[] _data;
}

void Container::resize(){
    _capacity = _capacity == 0 ? 1 : _capacity * 2; 
    
    Figure **new_data = new Figure*[_capacity];

    for(size_t i = 0; i < _size; i++)
        new_data[i] = std::move(_data[i]);
    
    delete[] _data;
    _data = new_data;
}

void Container::push_back(Figure &fig){
    if(_size >= _capacity)
        resize();
    _data[_size] = &fig;
    _size++;
}

void Container::erase(size_t ind) {
    if(ind >= _size)
        throw std::out_of_range("index out of range");
    for(int i = ind; i < _size - 1; ++i)
        _data[i] = std::move(_data[i + 1]);
    
    _size--;
}

size_t Container::size() const {
    return _size;
}

Container::operator double() const{
    double res = 0.0;
    for(size_t i = 0; i < _size; i++)
        res += static_cast<double>(*_data[i]);
    return res;
}

std::ostream &operator<<(std::ostream &os, const Container &con){
    for(size_t i = 0; i < con._size; i++) {
        Point figCenter = con._data[i]->center();
        os << "Figure[" << i << "] : ";
        os << *con._data[i] << std::endl;
        os << "Area : " << static_cast<double>(*con._data[i]) << std::endl;
        os << "Center : " << figCenter << std::endl;
    }
    return os;
}

Figure &Container::operator[](size_t index){
    return *_data[index];
}

