#include "httpmanager.h"

HttpManager::~HttpManager()
{
    std::cout<<"~HttpManager"<<std::endl;
}

HttpManager::HttpManager()
    :httpManager_(new QNetworkAccessManager(this))
{

    connect(this,&HttpManager::post_finished,this,&HttpManager::PostRequest);
    connect(this,&HttpManager::sign_http_finished,this,&HttpManager::slot_http_finish);
}

void HttpManager::PostRequest(const QUrl url, QJsonObject jsondata, ReqId reqid, Modules mod)
{
    // 前期准备
    QNetworkRequest request(url);
    auto data = QJsonDocument(jsondata).toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    auto self = shared_from_this();

    // 发送请求
    QNetworkReply* reply = httpManager_->post(request,data);
    connect(reply,&QNetworkReply::finished,this,[&](){
        if(reply->error() != QNetworkReply::NoError){   // 存在错误
            qDebug()<<"PostRequest error : "<<reply->error();
            emit sign_http_finished(reqid,"",mod,ERR_NETWORK);
            reply->deleteLater();
            return ;
        }

        QString response = reply->readAll();
        emit sign_http_finished(reqid,response,mod,SUCCESS);
        reply->deleteLater();
        return ;
    });
}

void HttpManager::slot_http_finish(ReqId reqid, QString response, Modules mod, ErrorCodes errorcode)
{
    switch (mod) {
    case Modules::REGISTERMOD:
        emit sig_reg_mod_finish(reqid,response,errorcode);
        break;
    default:
        break;
    }
}
