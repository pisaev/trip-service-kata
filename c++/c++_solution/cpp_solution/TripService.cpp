﻿#include "pch.h"
#include "TripService.h"

#include <list>

std::list<Trip> TripService::findTripsByUser(User& user) const
{
	return tripDao_->FindTripsBy(user);
}

std::list<Trip> TripService::GetTripsByUser(User& user) const
{
	const auto logged_user = UserSession::GetInstance()->GetLoggedUser();
	return GetTripsByUser(user, logged_user);
}

std::list<Trip> TripService::GetTripsByUser(User& user, User* loggedUser) const
{
	if (!loggedUser){
		throw UserNotLoggedInException("UserNotLoggedInException");
	}

	if (user.isFriendWith(*loggedUser)){
		return findTripsByUser(user);
	}

	return NO_TRIPS;
}
