#ifndef FECHO_
#define FECHO_

#include <cstddef>   // Para std::size_t
#include <stdexcept> // Para std::out_of_range

template <typename T>
class Fecho
{
private:
    T *m_data;              // Ponteiro para o array de elementos
    std::size_t m_size;     // Tamanho atual do fecho
    std::size_t m_capacity; // Capacidade atual do fecho

public:
    // Construtor padrão
    Fecho() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Construtor com tamanho inicial
    explicit Fecho(std::size_t size) : m_data(new T[size]), m_size(size), m_capacity(size) {}

    // Destrutor
    ~Fecho()
    {
        delete[] m_data;
    }

    // Retorna o tamanho atual do fecho
    std::size_t size() const
    {
        return m_size;
    }

    // Retorna true se o fecho estiver vazio, false caso contrário
    bool empty() const
    {
        return m_size == 0;
    }

    // Retorna a capacidade atual do fecho
    std::size_t capacity() const
    {
        return m_capacity;
    }

    // Adiciona um elemento ao final do fecho
    void push_back(const T &value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        m_data[m_size] = value;
        ++m_size;
    }

    // Acessa o elemento no índice especificado
    T &operator[](std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Índice fora dos limites");
        }

        return m_data[index];
    }

    // Retorna o elemento no índice especificado
    const T &operator[](std::size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Índice fora dos limites");
        }

        return m_data[index];
    }

    // Redimensiona o fecho para conter o novo tamanho
    void resize(std::size_t newSize)
    {
        if (newSize > m_capacity)
        {
            reserve(newSize);
        }

        m_size = newSize;
    }

    // Aumenta a capacidade do fecho para o valor especificado
    void reserve(std::size_t newCapacity)
    {
        if (newCapacity > m_capacity)
        {
            T *newData = new T[newCapacity];
            for (std::size_t i = 0; i < m_size; ++i)
            {
                newData[i] = m_data[i];
            }

            delete[] m_data;
            m_data = newData;
            m_capacity = newCapacity;
        }
    }

    // Operador de atribuição
    Fecho<T> &operator=(const Fecho<T> &other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for (std::size_t i = 0; i < m_size; ++i)
            {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }
};

#endif
