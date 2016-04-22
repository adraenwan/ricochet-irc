#ifndef IRCSERVER_H
#define IRCSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QByteArray>
#include <QHash>

class IrcChannel;
class IrcConnection;
class IrcUser;

class IrcServer : public QObject
{
    Q_OBJECT
public:
    explicit IrcServer(QObject *parent = 0,
                       uint16_t port = 6667,
                       const QString& password = QStringLiteral(""));
    ~IrcServer();

    IrcChannel* getChannel(QString channel_name);

    IrcUser* findUser(const QString& nickname);

    /**
     * @brief send a raw IRC message to everyone in a channel
     * @param channel IRC channel boject
     * @param msg raw message
     * @param sender IRC user
     * @param include_sender also send to the sender themselves?
     */
    void channelMessage(IrcChannel* channel, QString msg, IrcUser* sender, bool include_sender);

    /**
     * @brief broadcast send message to EVERYONE
     * @param msg
     * @param sender
     */
    void broadcast(IrcUser* sender, QString msg);

    virtual const QString getWelcomeMessage();

signals:

public slots:
    /**
     * @brief main entry point. invoke this slot to start the server.
     */
    bool run();

    void newConnection();

    void clientLoggedIn();

    /**
     * @brief IrcServer::privmsg slot for incoming PRIVMSGs; relays them to all recipients
     * @param user sender
     * @param msgtarget
     * @param text
     */
    void privmsg(IrcUser*, const QString&, const QString&);

    void joined(IrcUser*, const QString&);

    void flagsChanged(IrcUser *member);

    void rename(IrcUser* member, const QString& new_nick);

    void part(IrcConnection* conn, const QString& channel);

    void quit(IrcUser* conn);

    void disconnect(IrcConnection* conn);

    void topicChanged(IrcUser* sender, IrcChannel* channel);


protected:
    uint16_t port;
    QString password;
    QString welcome_message;

    QTcpServer *tcpServer;
    QHash<QTcpSocket*, IrcConnection*> clients;
    QHash<QString, IrcChannel*> channels;

    /**
     * @brief privmsgHook called after a PRIVMSG was processed
     * Override this to implement a bot.
     */
    virtual void privmsgHook(IrcUser*, const QString&, const QString&) {}

    /**
     * @brief ircUserLoggedIn A new user connected successfully.
     * @param conn
     */
    virtual void ircUserLoggedIn(IrcConnection* conn = 0) {
        Q_UNUSED(conn);
    };

    /**
     * @brief ircUserLeft A user quit and/or disconnected
     */
    virtual void ircUserLeft(IrcConnection* conn = 0) {
        Q_UNUSED(conn);
    };

};

#endif // IRCSERVER_H
