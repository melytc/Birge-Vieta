
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Función que hace la división sintética de un polinomio con una x determinada.
double DivisionSintetica(vector<double> vecPolinomio, int iGrado, double dRaiz, bool bDivision)
{
    // Vector para guardar las derivadas de los polinomios.
    vector<double> vecDerivada;
    double dEvaluacion = vecPolinomio[iGrado];
    
    // Evalúa el polinomio.
    for (int i = iGrado - 1; i >= 0; i--)
    {
        dEvaluacion *= dRaiz;
        dEvaluacion += vecPolinomio[i];
        vecDerivada.insert(vecDerivada.begin(), dEvaluacion);
    }
    
    // Calcula la división de la función evaluada entre la derivada evaluada.
    if (bDivision)
    {
        double dDerivada = vecPolinomio[iGrado];
        
        // Calcula la derivada.
        for (int i = iGrado-1; i >= 1; i--)
        {
            dDerivada *= dRaiz;
            dDerivada += vecDerivada[i];
        }
        return dEvaluacion/dDerivada;
    }
    
    // Regresa la evaluación de la función.
    else
        return dEvaluacion;
}

int main()
{
    char cRepetir;
    double dToleranciaError, dCoeficiente, dRaiz;
    int iGrado, iMaximoIteraciones;
    
    vector<double> vecPolinomio;
    
    cout << "Método de Birge-Vieta" << endl;
    do
    {
        // Lee el polinomio, la tolerancia de error y el máximo de iteraciones.
        cout << "¿Cuál es el grado del polinomio? ";
        cin >> iGrado;
        
        for(int i = iGrado; i > 0; i--)
        {
            cout << "¿Cuál es el coeficiente para el término de grado " << i << "? ";
            cin >> dCoeficiente;
            vecPolinomio.insert(vecPolinomio.begin(), dCoeficiente);
        }
        cout << "¿Cuál es el valor de la constante? ";
        cin >> dCoeficiente;
        vecPolinomio.insert(vecPolinomio.begin(), dCoeficiente);
        
        cout << "¿Cuál es la tolerancia de error en decimal?" << endl;
        cin >> dToleranciaError;
        
        cout << "¿Cuál es el número máximo de iteraciones?" << endl;
        cin >> iMaximoIteraciones;
        
        int iRaices = 1;
        // Empezamos con x = 0.5 por decir un número aleatorio.
        dRaiz = 0.5;
        
        while (iGrado > 0)
        {
            int iIteracionesRestantes = iMaximoIteraciones;
            
            // Va aproximando la raiz mientras la evaluación sea mayor a la tolerancia de error y mientras
            // haya iteraciones restantes.
            do
                dRaiz -= DivisionSintetica(vecPolinomio, iGrado, dRaiz, 1);
            
            while ((dToleranciaError < fabs(DivisionSintetica(vecPolinomio, iGrado, dRaiz, 0))) && (iIteracionesRestantes-- > 0));
            
            // Si se salió porque la evaluación es menor a la tolerancia de error, muestra la raíz y calcula
            // el polinomio de grado (gradoActual - 1) para sacar otra raíz.
            if (iIteracionesRestantes > 0)
            {
                cout << "Raiz #" << iRaices++ << " es: " << dRaiz << endl;
                
                double y = vecPolinomio[iGrado];
                for (int i = iGrado - 1; i >= 1; i--)
                {
                    y *= dRaiz;
                    y += vecPolinomio[i];
                    vecPolinomio[i] = y;
                }
                vecPolinomio.erase(vecPolinomio.begin());
                iGrado--;
            }
            else
            {
                cout << "No quedan más raíces reales." << endl;
                break;
            }
        }
        
        // Vacía el vector por si se resuelve otro polinomio.
        vecPolinomio.clear();
        
        cout << "¿Desea resolver otro polinomio? s/n ";
        cin >> cRepetir;
    }
    while(cRepetir == 's');
    
    return 0;
}