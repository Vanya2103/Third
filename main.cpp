#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

bool isValidEmail(const QString& email) {
    QRegularExpression pattern(R"(^[\w.%+-]+@[\w.-]+\.[A-Za-z]{2,}$)");
    QRegularExpressionMatch match = pattern.match(email);
    return match.hasMatch();
}

class EmailValidatorWidget : public QWidget {
    Q_OBJECT

public:
    EmailValidatorWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        emailInput = new QLineEdit(this);
        emailInput->setPlaceholderText("Введите email");

        validateButton = new QPushButton("Проверить", this);

        emailListView = new QListView(this);
        emailListModel = new QStringListModel(this);
        emailListView->setModel(emailListModel);

        layout->addWidget(emailInput);
        layout->addWidget(validateButton);
        layout->addWidget(emailListView);

        connect(validateButton, &QPushButton::clicked, this, &EmailValidatorWidget::validateEmail);
    }

private slots:
    void validateEmail() {
        QString email = emailInput->text();
        if (isValidEmail(email)) {
            emailListModel->insertRow(emailListModel->rowCount());
            QModelIndex index = emailListModel->index(emailListModel->rowCount() - 1);
            emailListModel->setData(index, email + " - Верный");
        } else {
            emailListModel->insertRow(emailListModel->rowCount());
            QModelIndex index = emailListModel->index(emailListModel->rowCount() - 1);
            emailListModel->setData(index, email + " - Неверный");
        }
    }

private:
    QLineEdit *emailInput;
    QPushButton *validateButton;
    QListView *emailListView;
    QStringListModel *emailListModel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EmailValidatorWidget widget;
    widget.setWindowTitle("Проверятель");
    widget.show();

    return app.exec();
}

#include "main.moc"
