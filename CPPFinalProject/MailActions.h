#pragma once

#ifndef MAILACTIONS_H
#define MAILACTIONS_H

#include <iostream>
#include <memory>
#include <conio.h>

enum MailActions;

class MailActionsManager
{

private:
    std::unique_ptr<MailActions> action;

public:
	MailActionsManager();
    MailActionsManager(MailActionsManager&& mailActions) noexcept;
    void MakingAction();
	~MailActionsManager();
};

enum MailActions
{
    GettingMail,
    GivingMail,
    makingPaynment,
    purchasingProudct
};
#endif 
