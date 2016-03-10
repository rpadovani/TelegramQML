#ifndef TELEGRAMAUTHENTICATE_H
#define TELEGRAMAUTHENTICATE_H

#include <QObject>

#include "telegramqml_macros.h"
#include "tqobject.h"

class TelegramEngine;
class TelegramAuthenticatePrivate;
class TELEGRAMQMLSHARED_EXPORT TelegramAuthenticate : public TqObject
{
    Q_OBJECT
    Q_ENUMS(AuthState)
    Q_PROPERTY(TelegramEngine* engine READ engine WRITE setEngine NOTIFY engineChanged)
    Q_PROPERTY(int state READ state NOTIFY stateChanged)
    Q_PROPERTY(int callTimeout READ callTimeout NOTIFY callTimeoutChanged)
    Q_PROPERTY(int remainingTime READ remainingTime NOTIFY remainingTimeChanged)

public:
    enum AuthState {
        AuthUnknown = 0,
        AuthCheckingPhone = 1,
        AuthCheckingPhoneError = 2,
        AuthSignUpNeeded = 3,
        AuthCodeRequesting = 4,
        AuthCodeRequestingError = 5,
        AuthCodeRquested = 6,
        AuthLoggingIn = 7,
        AuthLoggingInError = 8,
        AuthLoggedIn = 9
    };

    TelegramAuthenticate(QObject *parent = 0);
    ~TelegramAuthenticate();

    TelegramEngine *engine() const;
    void setEngine(TelegramEngine *engine);

    int state() const;
    int callTimeout() const;
    int remainingTime() const;

public Q_SLOTS:
    void signUp(const QString &firstName, const QString &lastName);
    void signIn(const QString &code);

Q_SIGNALS:
    void engineChanged();
    void stateChanged();
    void callTimeoutChanged();
    void remainingTimeChanged();
    void authLoggedIn();

protected:
    virtual void refresh();
    virtual void clean();
    void startRemainingTimer(int time);

private:
    void requestCode();
    void switchState(int state);

private:
    TelegramAuthenticatePrivate *p;
};

#endif // TELEGRAMAUTHENTICATE_H