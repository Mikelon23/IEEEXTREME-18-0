#include <iostream>
#include <vector>

using namespace std;

int change(int amount, vector<int>& coins) {
    // Creamos un vector dp de tamaño amount+1 y lo inicializamos en 0
    vector<int> dp(amount + 1, 0);
    
    // Inicializamos dp[0] a 1 porque hay una forma de hacer el monto 0, usando 0 monedas.
    dp[0] = 1;
    
    // Iteramos a través de cada moneda
    for (int coin : coins) {
        // Para cada moneda, actualizamos dp desde coin hasta amount
        for (int i = coin; i <= amount; ++i) {
            dp[i] += dp[i - coin];
        }
    }
    
    // El resultado es el número de formas de formar el monto "amount"
    return dp[amount];
}

int main() {
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 5;
    cout << "Number of ways to make amount " << amount1 << ": " << change(amount1, coins1) << endl;

    vector<int> coins2 = {2};
    int amount2 = 3;
    cout << "Number of ways to make amount " << amount2 << ": " << change(amount2, coins2) << endl;

    vector<int> coins3 = {10};
    int amount3 = 10;
    cout << "Number of ways to make amount " << amount3 << ": " << change(amount3, coins3) << endl;

    return 0;
}
 //a simple exercise