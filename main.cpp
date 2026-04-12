#include <iostream>
#include <string>

class HttpClient {
public:
     std::string get(const std::string&url) {
        std::cout << "Connecting to: " << url << std::endl;


        return "{ 'ststus':   'ok'  }";
     }
};

int main() {
      HttpClient client;

      std::string response =
          client.get("https://api.game-service.com/login");
        
       std::cout <<  response << std::endl;


if (verifyCertificate(serverCert) && matchDomain(serverCert)) {
 
    allowConnection();
}
 else {
  
    blockConnection();
};


bool isTrustedServer(const std::string& domain,
                     const std::string& certCN) {

    return domain == certCN;
}

int main() {
    std::string domain = "api.game.com";
    std::string certCN = "api.game.com"; // пришло от TLS

    if (isTrustedServer(domain, certCN)) {
        std::cout << "Secure connection\n";
    } else {
        std::cout << "WARNING: possible spoofing\n";
    }
}


};