#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <Singleton.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <global.h>

class HttpManager : public QObject, public Singleton<HttpManager>
    , public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT

    friend class Singleton<HttpManager>;
public:
    ~HttpManager();
private:
    HttpManager();
    void PostRequest(const QUrl url,QJsonObject jsondata,ReqId reqid,Modules mod);
private:
    QNetworkAccessManager* httpManager_;
private slots:
    void slot_http_finish(ReqId reqid,QString response,Modules mod,ErrorCodes errorcode);
signals:
    void post_finished(const QUrl url,QJsonObject jsondata,ReqId reqid,Modules mod);
    void sign_http_finished(ReqId reqid,QString response,Modules mod,ErrorCodes errorcode);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
