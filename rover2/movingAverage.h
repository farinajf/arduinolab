#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

template <typename V, int N> class MovingAverage {
  private:
    V _vector[N]; //Vector de dimension N
    V _suma;      //Suma movil
    V _p;         //Puntero
  
    /**
     * void _check()
     * 
     * _p debe apuntar a un elemento del vector
     */
    void _check() {
      
    }
    
  public:
    MovingAverage(V x = 0) : _suma(0), _p(0) {
      for (int i = 0; i < N; i++)
      {
        _vector[i] = x;
        _suma     += _vector[i];
      }
    }
    
    /**
     * V add(V x)
     */
    V add(V x) {
      //1.- Actualiza la suma movil
      _suma += (x - _vector[_p]);
      
      //2.- Anhade la nueva muestra (se sustituye por la mas antigua)
      _vector[_p++] = x;
      
      //3.- Se mueve el puntero una posicion
      if (_p >= N) _p = 0;
      
      //4.- Fin
      return _suma/N;
    }
  
};

#endif
