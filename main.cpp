#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>

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
        emailInput->setPlaceholderText("Введите электронную почту");

        validateButton = new QPushButton("Validate", this);

        resultLabel = new QLabel(this);

        layout->addWidget(emailInput);
        layout->addWidget(validateButton);
        layout->addWidget(resultLabel);

        connect(validateButton, &QPushButton::clicked, this, &EmailValidatorWidget::validateEmail);
    }

private slots:
    void validateEmail() {
        QString email = emailInput->text();
        if (isValidEmail(email)) {
            resultLabel->setText("Корректный адрес электронной почты.");
        } else {
            resultLabel->setText("Некорректный адрес электронной почты.");
        }
    }

private:
    QLineEdit *emailInput;
    QPushButton *validateButton;
    QLabel *resultLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EmailValidatorWidget widget;
    widget.setWindowTitle("Email Validator");
    widget.show();

    return app.exec();
}

#include "main.moc"
