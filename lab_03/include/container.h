#include <figure.h>

class Container
{
private:
    void resize();
    size_t _size;
    size_t _capacity;
    Figure** _data;
public:
    Container();
    ~Container();

    operator double() const;
    Figure &operator[](size_t index);

    void push_back(Figure &fig);
    void erase(size_t ind);

    size_t size() const;
    Figure &begin();
    Figure &end();

    friend std::ostream &operator<<(std::ostream &os, const Container &con);
};
