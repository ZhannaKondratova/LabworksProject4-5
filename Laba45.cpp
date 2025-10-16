#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::transform, std::tolower

class Diode {
public:
    Diode() : forwardVoltage(0.0), maxReverseCurrent(0.0), purpose("") {}
    Diode(double fv, double mrc, const std::string& purp) {
        setForwardVoltage(fv);
        setMaxReverseCurrent(mrc);
        setPurpose(purp);
    }
    ~Diode() {}
    void input() {
        std::cout << "Enter forward voltage (V): "; 
        double fv;
        std::cin >> fv;
        setForwardVoltage(fv);

        std::cout << "Enter maximum reverse current (mA): "; 
        double mrc;
        std::cin >> mrc;
        setMaxReverseCurrent(mrc);

        std::cout << "Enter the diode's purpose: "; 
        std::getline(std::cin >> std::ws, purpose);
    }
    void output() const {
        std::cout << "Diode:" << std::endl; 
        std::cout << "  Forward Voltage: " << forwardVoltage << " V" << std::endl; 
        std::cout << "  Max. Reverse Current: " << maxReverseCurrent << " mA" << std::endl; 
        std::cout << "  Purpose: " << purpose << std::endl;
    }
  
    bool matchesCriteria(double minVf, double maxIrmax, const std::string& searchPurp) const {
        bool matchesVf = (minVf <= 0.0) || (forwardVoltage >= minVf);
        bool matchesIrmax = (maxIrmax <= 0.0) || (maxReverseCurrent <= maxIrmax);
        bool matchesPurpose = searchPurp.empty();
        if (!searchPurp.empty()) {
            std::string purp_lower = purpose;
            std::string search_lower = searchPurp;

            std::transform(purp_lower.begin(), purp_lower.end(), purp_lower.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            std::transform(search_lower.begin(), search_lower.end(), search_lower.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            matchesPurpose = (purp_lower.find(search_lower) != std::string::npos);
        }
        return matchesVf && matchesIrmax && matchesPurpose;
    }
    void setForwardVoltage(double fv) {
        if (fv >= 0.0)
            forwardVoltage = fv;
        else
            std::cout << "Error! Voltage cannot be negative." << std::endl; 
    }
    void setMaxReverseCurrent(double mrc) {
        if (mrc >= 0.0)
            maxReverseCurrent = mrc;
        else
            std::cout << "Error! Current cannot be negative." << std::endl; 
    }
    void setPurpose(const std::string& purp) {
        purpose = purp;
    }
private:
    double forwardVoltage;     
    double maxReverseCurrent;  
    std::string purpose;       
};
void filterAndOutputDiodes(const std::vector<Diode>& diodes, double minVf, double maxIrmax, const std::string& searchPurp) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "Diode Filtering:" << std::endl; // Фільтрація діодів:
    std::cout << "Criterion: Vf >= " << minVf << " V, Irmax <= " << maxIrmax << " mA, Purpose contains: '" << searchPurp << "'" << std::endl; 
    std::cout << "==========================================" << std::endl;
    bool found = false;
    int count = 0;
    for (const auto& d : diodes) {
        if (d.matchesCriteria(minVf, maxIrmax, searchPurp)) {
            d.output();
            std::cout << "------------------------------------------" << std::endl;
            found = true;
            count++;
        }
    }
    if (!found) {
        std::cout << "No diode matching the specified criteria was found." << std::endl; 
    } else {
        std::cout << "Found " << count << " diodes matching the criteria." << std::endl; 
    }
}
int main() {
    std::cout << "Enter information for the first diode:" << std::endl; 
    Diode d1;
    d1.input();

    Diode d2(0.7, 0.01, "Current Rectifier"); 
    Diode d3(2.1, 0.005, "Light Emitting Diode (LED)"); 
    Diode d4(0.3, 1.0, "Schottky Diode for high-speed circuits"); 
    Diode d5(0.6, 0.05, "Low-power general-purpose diode"); 
    std::vector<Diode> allDiodes;
    allDiodes.push_back(d1);
    allDiodes.push_back(d2);
    allDiodes.push_back(d3);
    allDiodes.push_back(d4);
    allDiodes.push_back(d5);

    std::cout << "\n=== All entered/created diode information ===" << std::endl;
    for (const auto& d : allDiodes) {
        d.output();
        std::cout << "------------------------------------------" << std::endl;
    }
    filterAndOutputDiodes(allDiodes, 0.7, 0.0, "");
    filterAndOutputDiodes(allDiodes, 0.0, 0.01, "diode");
    filterAndOutputDiodes(allDiodes, 0.0, 100.0, "rectifier");
    filterAndOutputDiodes(allDiodes, 5.0, 0.0, "");
    return 0;
}

