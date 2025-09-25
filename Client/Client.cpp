#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define FONT(f) UI::Font::FontToString(UI::Fonts::f)

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <iostream>
#include <regex>
#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <cstdint>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

#include <fmt/core.h>
#include <fmt/color.h>

#include <SFML/Network.hpp>

#include "Widgets/Font.hpp"
#include "Widgets/Label.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/ButtonWithImage.hpp"
#include "Widgets/InputField.hpp"
#include "Widgets/Checkbox.hpp"

#include "Helper/Helper.hpp"


sf::TcpSocket clientSocket;
std::mutex clientSocketMutex;


bool setupClinetNetowrking() {
    auto ipOpt = sf::IpAddress::resolve("127.0.0.1");
    if (!ipOpt) {
        std::cerr << "Invalid IP address\n";
        return false;
    }
    sf::IpAddress serverIp = ipOpt.value();
    unsigned short serverPort = 54000;

    if (clientSocket.connect(serverIp, serverPort) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server\n";
        return false;
    }

    std::cout << "Connected to the server!" << std::endl;
    clientSocket.setBlocking(false);
    return true;
}

void sendPacket(const std::string& msg) {
    std::lock_guard<std::mutex> lock(clientSocketMutex);
    if (clientSocket.send(msg.c_str(), msg.size()) != sf::Socket::Status::Done) std::cerr << "Failed to send packet\n";
}

struct BeforeRegisterSettings {
    std::string fullname = "", mail = "", password = "", hwid = "";
};

struct LoginSettings {
    std::string fullname = "", mail = "", password = "", hwid = "";
};

enum class ScreenState {
    SIGN_IN,
    SIGN_UP,
    FORGOT_PASSWORD,
    EMAIL_VERIFICATION,
    MAIN_MENU
};

int main() {
    EnableANSIColors();

    if (!setupClinetNetowrking()) system("PAUSE");

    BeforeRegisterSettings BeforeRegister;
    LoginSettings LoginSetting;


	/* ----------- SETUP THE UI -------------- */

	sf::VideoMode videoMode{ sf::Vector2u(1920, 1080) };

	sf::RenderWindow window;
	window.create(videoMode, "TaskFlow", sf::State::Fullscreen);
	window.setFramerateLimit(60);
    sf::Vector2u windowSize = window.getSize();


    ScreenState current = ScreenState::SIGN_IN;
    sendPacket("action|remember_me\nhwid|" + getHWID() + "\n");


	/* ----------- ADD WIDGETS --------------- */


    // Background & Wallpaper
    sf::Texture bgTextureLogin;
    if (!bgTextureLogin.loadFromFile("Cache/Interface/loginWallpaper.jpg")) {
        throw std::runtime_error("Failed to load loginWallpaper.jpg");
    }
    bgTextureLogin.setSmooth(true);
    sf::Vector2u bgTextureLoginSize = bgTextureLogin.getSize();

    sf::Sprite backgroundLogin(bgTextureLogin);
    backgroundLogin.setScale({
        1920.f / bgTextureLoginSize.x,
        1080.f / bgTextureLoginSize.y
    });



    // Form Box
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(560.f, 700.f));
    rectangle.setFillColor(sf::Color(255, 255, 255, 100));
    rectangle.setOutlineThickness(2.f);
    rectangle.setOutlineColor(sf::Color(255, 255, 255, 150));

    sf::Vector2f rectSize = rectangle.getSize();

    rectangle.setPosition({
        (windowSize.x - rectSize.x) / 2.f,
        (windowSize.y - rectSize.y) / 2.f
    });
    


    // Titles SignIN
    UI::Label Title(
        "Welcome Back",
        FONT(Kenyan_Coffee_Bd),
        58,
        sf::Color(28, 28, 42)
    );
    Title.setPosition({ 830, 230 });

    UI::Label Title2(
        "Sign in to your account",
        FONT(Autoradiographic_Rg_It),
        22,
        sf::Color(46, 46, 62)
    );
    Title2.setPosition({ 870, 320 });



    // InputField SignIN
    UI::TextInput gmailInput("MAIL", FONT(Autoradiographic_Rg_It), {760, 400}, 24, {400.f, 40.f}, sf::Color(255, 255, 255, 150), sf::Color::Black);
    UI::TextInput passwordInput("PASSWORD", FONT(Autoradiographic_Rg_It), { 760, 485 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);

    UI::Label gmailInputText("E-Mail Address", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    gmailInputText.setPosition({ 770, 405 });

    UI::Label passwordInputText("Password", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    passwordInputText.setPosition({ 770, 490 });

    UI::Label signinError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    signinError.setPosition({ 760, 450 });


    // Checkbox SignIN
    UI::Checkbox remember_me(
        { 762, 560 },
        20.f,
        sf::Color::White,
        sf::Color::Black,
        2.f
    );
    UI::Label remember_me_text("Remember Me", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    remember_me_text.setPosition({ 790, 558 });



    // Forgot password
    UI::Label forgot_password("Forgot password?", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    forgot_password.setPosition({ 1052, 560 });
    forgot_password.setOnClick([&]() {
        current = ScreenState::FORGOT_PASSWORD;
    });



    // or continue with SignIN
    sf::RectangleShape continueWithLine1;
    continueWithLine1.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine1.setFillColor(sf::Color::White);
    continueWithLine1.setPosition({ 760, 710 });

    UI::Label or_continue_with("or continue with", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    or_continue_with.setPosition({ 912, 698 });

    sf::RectangleShape continueWithLine2;
    continueWithLine2.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine2.setFillColor(sf::Color::White);
    continueWithLine2.setPosition({ 1030, 710 });



    // google & github login

    sf::Texture googleTexture, githubTexture;
    if (!googleTexture.loadFromFile("Cache/Interface/google.png")) {
        throw std::runtime_error("Failed to load google logo texture!");
    }
    if (!githubTexture.loadFromFile("Cache/Interface/github.png")) {
        throw std::runtime_error("Failed to load github logo texture!");
    }

    googleTexture.setSmooth(true);
    githubTexture.setSmooth(true);

    sf::Sprite googleLogo(googleTexture);
    sf::Sprite githubLogo(githubTexture);

    googleLogo.setScale(sf::Vector2f(0.07, 0.07));
    googleLogo.setPosition(sf::Vector2f(790, 758));

    githubLogo.setScale(sf::Vector2f(0.55, 0.55));
    githubLogo.setPosition(sf::Vector2f(1010, 757));



    // Don't have an account?
    UI::Label signupText("Don't have an account?", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    signupText.setPosition({ 835, 830 });

    UI::Label signup("Sign up", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    signup.setPosition({ 985, 830 });
    signup.setOnClick([&]() {
        current = ScreenState::SIGN_UP;
    });







    // Titles SignUP
    UI::Label TitleRegister(
        "Register",
        FONT(Kenyan_Coffee_Bd),
        58,
        sf::Color(28, 28, 42)
    );
    TitleRegister.setPosition({ 875, 230 });

    UI::Label TitleRegister2(
        "Sign up a new account",
        FONT(Autoradiographic_Rg_It),
        22,
        sf::Color(46, 46, 62)
    );
    TitleRegister2.setPosition({ 870, 320 });



    // InputField SignUP
    UI::TextInput fullNameInputRegister("FULLNAME", FONT(Autoradiographic_Rg_It), { 760, 400 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);
    UI::TextInput gmailInputRegister("MAIL", FONT(Autoradiographic_Rg_It), { 760, 485 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);
    UI::TextInput passwordInputRegister("PASSWORD", FONT(Autoradiographic_Rg_It), { 760, 570 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);

    UI::Label fullNameInputTextRegister("Name and Surname", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    fullNameInputTextRegister.setPosition({ 770, 405 });

    UI::Label gmailInputTextRegister("E-Mail", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    gmailInputTextRegister.setPosition({ 770, 490 });

    UI::Label passwordInputTextRegister("Password", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    passwordInputTextRegister.setPosition({ 770, 575 });


    UI::Label fullNameRegisterError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    fullNameRegisterError.setPosition({ 760, 450 });

    UI::Label gmailRegisterError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    gmailRegisterError.setPosition({ 760, 534 });

    UI::Label passwordRegisterError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    passwordRegisterError.setPosition({ 760, 620 });



    // or continue with SignUP
    sf::RectangleShape continueWithLine11;
    continueWithLine11.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine11.setFillColor(sf::Color::White);
    continueWithLine11.setPosition({ 760, 770 });

    UI::Label or_continue_with2("or continue with", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    or_continue_with2.setPosition({ 912, 758 });

    sf::RectangleShape continueWithLine22;
    continueWithLine22.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine22.setFillColor(sf::Color::White);
    continueWithLine22.setPosition({ 1030, 770 });



    // Already have an account?
    UI::Label signinText("Already have an account?", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    signinText.setPosition({ 835, 830 });

    UI::Label signin("Sign in", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    signin.setPosition({ 1000, 830 });
    signin.setOnClick([&]() {
        current = ScreenState::SIGN_IN;
    });







    // Titles SignIN
    UI::Label TitleVerify(
        "Verify Mail",
        FONT(Kenyan_Coffee_Bd),
        58,
        sf::Color(28, 28, 42)
    );
    TitleVerify.setPosition({ 865, 230 });

    UI::Label Title2Verify(
        "We sent you a 4 digit-code!",
        FONT(Autoradiographic_Rg_It),
        22,
        sf::Color(46, 46, 62)
    );
    Title2Verify.setPosition({ 865, 320 });



    UI::TextInput codeInput("CODE", FONT(Autoradiographic_Rg_It), { 760, 400 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);
    
    UI::Label codeInputText("1234", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    codeInputText.setPosition({ 770, 405 });

    UI::Label codeInputError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    codeInputError.setPosition({ 760, 450 });

    UI::Label codeResend("Resend new code!", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    codeResend.setPosition({ 1052, 480 });
    codeResend.setOnClick([&]() {
        if (codeResend.getText() == "Resend new code!") {
            sendPacket("action|email_verification\nfullname|" + BeforeRegister.fullname + "\nmail|" + BeforeRegister.mail + "\npassword|" + BeforeRegister.password + "\n");
            codeResend.setText("Sent new code!");
            codeResend.setColor(sf::Color::Green);
        }
    });


    sf::RectangleShape continueWithLine33;
    continueWithLine33.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine33.setFillColor(sf::Color::White);
    continueWithLine33.setPosition({ 760, 710 });

    UI::Label or_continue_with33("or continue with", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    or_continue_with33.setPosition({ 912, 698 });

    sf::RectangleShape continueWithLine333;
    continueWithLine333.setSize(sf::Vector2f(130.f, 1.f));
    continueWithLine333.setFillColor(sf::Color::White);
    continueWithLine333.setPosition({ 1030, 710 });


    UI::Label backToSigninText("Back to Sign in?", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    backToSigninText.setPosition({ 865, 760 });

    UI::Label backtoSignIn("Sign in", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    backtoSignIn.setPosition({ 975, 760 });
    backtoSignIn.setOnClick([&]() {
        current = ScreenState::SIGN_IN;
    });





    UI::Label TitleFP(
        "Forgot Password",
        FONT(Kenyan_Coffee_Bd),
        58,
        sf::Color(28, 28, 42)
    );
    TitleFP.setPosition({ 812, 230 });


    UI::Label TitleFP2(
        "Request your credentials!",
        FONT(Autoradiographic_Rg_It),
        22,
        sf::Color(46, 46, 62)
    );
    TitleFP2.setPosition({ 865, 320 });



    UI::TextInput forgotPassInput("Mail", FONT(Autoradiographic_Rg_It), { 760, 400 }, 24, { 400.f, 40.f }, sf::Color(255, 255, 255, 150), sf::Color::Black);

    UI::Label forgotPassInputText("Your e-mail", FONT(Autoradiographic_Rg_It), 22, sf::Color(200, 200, 200));
    forgotPassInputText.setPosition({ 770, 405 });

    UI::Label forgotPassError("", FONT(Autoradiographic_Rg_It), 16, sf::Color::Red);
    forgotPassError.setPosition({ 760, 450 });


    UI::Label TitleFP3(
        "Your credentials are %100 safe withTaskFlow!",
        FONT(Autoradiographic_Rg_It),
        22,
        sf::Color(46, 46, 62)
    );
    TitleFP3.setPosition({ 788, 650 });



    UI::Label signinTextFP("Back to signin?", FONT(Autoradiographic_Rg_It), 18, sf::Color::White);
    signinTextFP.setPosition({ 880, 820 });

    UI::Label signinFP("Sign in", FONT(Autoradiographic_Rg_It), 18, sf::Color(153, 0, 153));
    signinFP.setPosition({ 980, 820 });
    signinFP.setOnClick([&]() {
        current = ScreenState::SIGN_IN;
    });

    






    // BUTTONS
    enum class ButtonID { SIGN_IN, GOOGLE_SIGN_IN, GITHUB_SIGN_IN, SIGN_UP, VERIFY, REQUEST };
    std::vector<std::pair<ButtonID, std::unique_ptr<UI::Button>>> buttons;

    auto addButton = [&](ButtonID id, const std::string& label, const sf::Vector2f& pos, const sf::Vector2f& size, sf::Color bg, sf::Color text) {
        auto btn = std::make_unique<UI::Button>(label, FONT(Kenyan_Coffee_Bd), 24, size, bg, text);
        btn->setPosition(pos);

        btn->setCallback([btnPtr = btn.get(), id,
            &current, &BeforeRegister, &signinError,
            &gmailInput, &passwordInput, &codeResend,
            &fullNameInputRegister, &gmailInputRegister, &passwordInputRegister,
            &fullNameRegisterError, &gmailRegisterError, &passwordRegisterError,
            &codeInput, &codeInputError,
            &forgotPassInput, &forgotPassError,
            &remember_me
        ]() {
                int bypassed = 0;
        switch (id) {
            case ButtonID::SIGN_IN:
                bypassed = 0;
                if (isValidPassword(passwordInput.getText())) signinError.setText(""), bypassed++;
                else signinError.setText("Must contain at least 6 characters, an uppercase & lower, number, special character!");

                if (isValidMail(gmailInput.getText())) signinError.setText(""), bypassed++;
                else signinError.setText("Must contain '@' and '.' Also needs to be a real mail address!");

                if (bypassed == 2) {
                    BeforeRegister.mail = gmailInput.getText();
                    BeforeRegister.password = passwordInput.getText();
                    
                    if (remember_me.isChecked()) BeforeRegister.hwid = getHWID();
                    else BeforeRegister.hwid = "";
                    
                    sendPacket("action|signin_default\nmail|" + BeforeRegister.mail + "\npassword|" + BeforeRegister.password + "\nhwid|" + BeforeRegister.hwid + "\n");
                }
                break;
            case ButtonID::GOOGLE_SIGN_IN:
                bypassed = 0;


                break;
            case ButtonID::GITHUB_SIGN_IN:
                bypassed = 0;


                break;
            case ButtonID::SIGN_UP:
                bypassed = 0;
                if (isValidFullName(fullNameInputRegister.getText())) bypassed++, fullNameRegisterError.setText("");
                else fullNameRegisterError.setText("This full-name is used to be fake!");

                if (isValidMail(gmailInputRegister.getText())) bypassed++, gmailRegisterError.setText("");
                else gmailRegisterError.setText("Must contain '@' and '.' Also needs to be a real mail address!");

                if (isValidPassword(passwordInputRegister.getText())) bypassed++, passwordRegisterError.setText("");
                else passwordRegisterError.setText("Must contain at least 6 characters, an uppercase & lower, number, special character!");

                if (bypassed == 3) {
                    current = ScreenState::EMAIL_VERIFICATION;

                    BeforeRegister.fullname = fullNameInputRegister.getText();
                    BeforeRegister.mail = gmailInputRegister.getText();
                    BeforeRegister.password = passwordInputRegister.getText();

                    sendPacket("action|email_verification\nfullname|" + BeforeRegister.fullname + "\nmail|" + BeforeRegister.mail + "\npassword|" + BeforeRegister.password + "\n");
                }

                break;
            case ButtonID::VERIFY:
                bypassed = 0;
                if (codeInput.getText().length() == 4 && !BeforeRegister.fullname.empty() && !BeforeRegister.mail.empty() && !BeforeRegister.password.empty()) {
                    sendPacket("action|check_code\nfullname|" + BeforeRegister.fullname + "\nmail|" + BeforeRegister.mail + "\npassword|" + BeforeRegister.password + "\ncode|" + codeInput.getText() + "\n");
                    codeInputError.setText("");
                    codeResend.setText("Resend new code!");
                    codeResend.setColor(sf::Color(153, 0, 153));
                }
                else codeInputError.setText("Code needs to be 4 digits!");

                break;
            case ButtonID::REQUEST:
                bypassed = 0;

                if (isValidMail(forgotPassInput.getText())) bypassed++, forgotPassError.setText("");
                else forgotPassError.setText("Must contain '@' and '.' Also needs to be a real mail address!");

                if (bypassed == 1) {
                    forgotPassError.setText("");
                    sendPacket("action|forgot_password\nmail|" + forgotPassInput.getText() + "\n");
                }

                break;
            default:
                break;
            }
        });

        buttons.push_back({ id, std::move(btn) });
    };

    addButton(ButtonID::GOOGLE_SIGN_IN, "        Google", { 760, 750 }, { 180, 50 }, sf::Color(255, 255, 255, 150), sf::Color::White);
    addButton(ButtonID::GITHUB_SIGN_IN, "        GitHub", { 980, 750 }, { 180, 50 }, sf::Color(255, 255, 255, 150), sf::Color::White);

    addButton(ButtonID::SIGN_IN, "Sign In", { 760, 620 }, { 400, 50 }, sf::Color(153, 0 ,153), sf::Color::White);
    addButton(ButtonID::SIGN_UP, "Sign Up", { 760, 665 }, { 400, 50 }, sf::Color(153, 0, 153), sf::Color::White);

    addButton(ButtonID::VERIFY, "Verify", { 760, 530 }, { 400, 50 }, sf::Color(153, 0, 153), sf::Color::White);
    addButton(ButtonID::REQUEST, "Request", { 760, 530 }, { 400, 50 }, sf::Color(153, 0, 153), sf::Color::White);




    while (window.isOpen()) {


        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
                switch (current) {
                    case ScreenState::SIGN_IN:
                        gmailInput.handleEvent(*e, window);
                        passwordInput.handleEvent(*e, window);

                        remember_me.handleEvent(*e, window);
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::SIGN_IN || id == ButtonID::GOOGLE_SIGN_IN || id == ButtonID::GITHUB_SIGN_IN) btn->handleEvent(*e, window);
                        }
                        signup.handleEvent(*e, window);
                        forgot_password.handleEvent(*e, window);

                        break;
                    case ScreenState::SIGN_UP:
                        fullNameInputRegister.handleEvent(*e, window);
                        gmailInputRegister.handleEvent(*e, window);
                        passwordInputRegister.handleEvent(*e, window);

                        signin.handleEvent(*e, window);
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::SIGN_UP) btn->handleEvent(*e, window);
                        }

                        break;
                    case ScreenState::FORGOT_PASSWORD:
                        forgotPassInput.handleEvent(*e, window);
                        signinFP.handleEvent(*e, window);
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::REQUEST) btn->handleEvent(*e, window);
                        }

                        break;
                    case ScreenState::EMAIL_VERIFICATION:
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::VERIFY) btn->handleEvent(*e, window);
                        }
                        codeInput.handleEvent(*e, window);
                        backtoSignIn.handleEvent(*e, window);
                        codeResend.handleEvent(*e, window);

                        break;
                    case ScreenState::MAIN_MENU:
                        
                        break;
                }
            }

            if (auto* e = event->getIf<sf::Event::MouseButtonReleased>()) {
                switch (current) {
                    case ScreenState::SIGN_IN:
                        gmailInput.handleEvent(*e, window);
                        passwordInput.handleEvent(*e, window);
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::SIGN_IN || id == ButtonID::GOOGLE_SIGN_IN || id == ButtonID::GITHUB_SIGN_IN) btn->handleEvent(*e, window);
                        }

                        break;
                    case ScreenState::SIGN_UP:
                        fullNameInputRegister.handleEvent(*e, window);
                        gmailInputRegister.handleEvent(*e, window);
                        passwordInputRegister.handleEvent(*e, window);

                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::SIGN_UP) btn->handleEvent(*e, window);
                        }

                        break;
                    case ScreenState::FORGOT_PASSWORD:
                        forgotPassInput.handleEvent(*e, window);
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::REQUEST) btn->handleEvent(*e, window);
                        }

                        break;
                    case ScreenState::EMAIL_VERIFICATION:
                        for (auto& [id, btn] : buttons) {
                            if (id == ButtonID::VERIFY) btn->handleEvent(*e, window);
                        }
                        codeInput.handleEvent(*e, window);
                        
                        break;
                    case ScreenState::MAIN_MENU:
                        
                        break;
                }
            }

            if (auto* e = event->getIf<sf::Event::TextEntered>()) {
                switch (current) {
                    case ScreenState::SIGN_IN:
                        gmailInput.handleEvent(*e);
                        passwordInput.handleEvent(*e);

                        break;
                    case ScreenState::SIGN_UP:
                        fullNameInputRegister.handleEvent(*e);
                        gmailInputRegister.handleEvent(*e);
                        passwordInputRegister.handleEvent(*e);

                        break;
                    case ScreenState::FORGOT_PASSWORD:
                        forgotPassInput.handleEvent(*e);

                        break;
                    case ScreenState::EMAIL_VERIFICATION:
                        codeInput.handleEvent(*e);
                        break;
                    case ScreenState::MAIN_MENU:
                        
                        break;
                }
            }
        }

        {
            char buffer[1024];
            std::size_t received;
            sf::Socket::Status status;
            {
                std::lock_guard<std::mutex> lock(clientSocketMutex);
                status = clientSocket.receive(buffer, sizeof(buffer), received);
            }

            if (status == sf::Socket::Status::Done) {
                std::string msg(buffer, received);

                auto data = parseMessage(msg);
                if (data["action"] == "verification" && has(data, "result") && has(data, "msg")) {
                    std::string result = get(data, "result");
                    if (result == "success") {
                        codeInputError.setText("");

                        signinError.setText("Successfully verified your account!");
                        signinError.setColor(sf::Color::Green);

                        current = ScreenState::SIGN_IN;
                    }
                    else codeInputError.setText(get(data, "msg"));
                }
                else if (data["action"] == "signin" && has(data, "result") && has(data, "msg")) {
                    std::string result = get(data, "result");
                    if (result == "success") {
                        signinError.setText("");
                        current = ScreenState::MAIN_MENU;
                    }
                    else {
                        signinError.setText(get(data, "msg"));
                        signinError.setColor(sf::Color::Red);
                    }
                }
                else if (data["action"] == "remember_me" && has(data, "result") && has(data, "fullname") && has(data, "gmail") && has(data, "password")) {
                    std::string result = get(data, "result");
                    if (result == "success") {
                        BeforeRegister.fullname.clear();
                        BeforeRegister.mail.clear();
                        BeforeRegister.password.clear();
                        BeforeRegister.hwid.clear();

                        LoginSetting.fullname = get(data, "fullname");
                        LoginSetting.mail = get(data, "gmail");
                        LoginSetting.password = get(data, "password");
                        LoginSetting.hwid = getHWID();

                        current = ScreenState::MAIN_MENU;
                    }
                }
                else if (data["action"] == "forgot_password" && has(data, "result") && has(data, "gmail") && has(data, "password")) {
                    std::string result = get(data, "result");
                    if (result == "success") {
                        forgotPassError.setText("");

                        signinError.setText("We sent your account credentials successfully!");
                        signinError.setColor(sf::Color::Green);

                        current = ScreenState::SIGN_IN;
                    }
                    else forgotPassError.setText(get(data, "password"));
                }
            }
            else if (status == sf::Socket::Status::Disconnected) {
                std::cout << "Server disconnected\n";
                window.close();
            }
        }




        window.clear(sf::Color::Black);


        window.draw(backgroundLogin);
        window.draw(rectangle);

        switch (current) {
            case ScreenState::SIGN_IN:
                Title.draw(window);
                Title2.draw(window);

                gmailInput.draw(window);
                if (gmailInput.getText().empty()) gmailInputText.draw(window);

                passwordInput.draw(window);
                if (passwordInput.getText().empty()) passwordInputText.draw(window);

                if (!signinError.getText().empty()) signinError.draw(window);

                remember_me.draw(window);
                remember_me_text.draw(window);

                forgot_password.draw(window);

                for (auto& [id, btn] : buttons) {
                    if (id == ButtonID::SIGN_IN || id == ButtonID::GOOGLE_SIGN_IN || id == ButtonID::GITHUB_SIGN_IN) btn->draw(window);
                }

                window.draw(continueWithLine1);
                window.draw(continueWithLine2);

                or_continue_with.draw(window);

                window.draw(googleLogo);
                window.draw(githubLogo);

                signupText.draw(window);
                signup.draw(window);

                break;
            case ScreenState::SIGN_UP:
                TitleRegister.draw(window);
                TitleRegister2.draw(window);


                fullNameInputRegister.draw(window);
                if (fullNameInputRegister.getText().empty()) fullNameInputTextRegister.draw(window);

                gmailInputRegister.draw(window);
                if (gmailInputRegister.getText().empty()) gmailInputTextRegister.draw(window);

                passwordInputRegister.draw(window);
                if (passwordInputRegister.getText().empty()) passwordInputTextRegister.draw(window);



                window.draw(continueWithLine11);
                or_continue_with2.draw(window);
                window.draw(continueWithLine22);

                signinText.draw(window);
                signin.draw(window);

                for (auto& [id, btn] : buttons) {
                    if (id == ButtonID::SIGN_UP) btn->draw(window);
                }

                if (!fullNameRegisterError.getText().empty()) fullNameRegisterError.draw(window);
                if (!gmailRegisterError.getText().empty()) gmailRegisterError.draw(window);
                if (!passwordRegisterError.getText().empty()) passwordRegisterError.draw(window);

                break;
            case ScreenState::FORGOT_PASSWORD:
                TitleFP.draw(window);
                TitleFP2.draw(window);
                TitleFP3.draw(window);

                forgotPassInput.draw(window);
                if (forgotPassInput.getText().empty()) forgotPassInputText.draw(window);
                if (!forgotPassError.getText().empty()) forgotPassError.draw(window);

                window.draw(continueWithLine11);
                or_continue_with2.draw(window);
                window.draw(continueWithLine22);

                signinFP.draw(window);
                signinTextFP.draw(window);

                for (auto& [id, btn] : buttons) {
                    if (id == ButtonID::REQUEST) btn->draw(window);
                }

                break;
            case ScreenState::EMAIL_VERIFICATION:
                TitleVerify.draw(window);
                Title2Verify.draw(window);

                codeInput.draw(window);
                if (codeInput.getText().empty()) codeInputText.draw(window);

                if (!codeInputError.getText().empty()) codeInputError.draw(window);
                codeResend.draw(window);

                for (auto& [id, btn] : buttons) {
                    if (id == ButtonID::VERIFY) btn->draw(window);
                }

                window.draw(continueWithLine33);
                or_continue_with33.draw(window);
                window.draw(continueWithLine333);

                backtoSignIn.draw(window);
                backToSigninText.draw(window);

                break;
            case ScreenState::MAIN_MENU:
                
                break;
        }
        

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


	return EXIT_SUCCESS;
}