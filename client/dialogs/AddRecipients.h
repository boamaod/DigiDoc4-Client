/*
 * QDigiDoc4
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

#include "CertificateHistory.h"
#include "widgets/AddressItem.h"
#include "widgets/ItemList.h"

#include <QDialog>
#include <QHash>

namespace Ui {
class AddRecipients;
}

class LdapSearch;
class QSslCertificate;

class AddRecipients final : public QDialog
{
	Q_OBJECT

public:
	explicit AddRecipients(ItemList* itemList, QWidget *parent = nullptr);
	~AddRecipients() final;

	QList<CKey> keys();
	bool isUpdated() const;

private:
	void addRecipientFromFile();
	void addRecipientFromHistory();
	void addRecipient(const QSslCertificate& cert, bool select = true);
	void addRecipientToRightPane(Item *item, bool update = true);

	AddressItem* itemListValue(ItemList *list, const CKey &cert);
	void search(const QString &term, bool select = false, const QString &type = {});
	void showError(const QString &msg, const QString &details = {});
	void showResult(const QList<QSslCertificate> &result, int resultCount, const QVariantMap &userData);

	static QString defaultUrl(QLatin1String key, const QString &defaultValue);

	Ui::AddRecipients *ui;
	QList<CKey> rightList;
	LdapSearch *ldap_person, *ldap_corp;
	bool updated = false;

	HistoryList historyCertData;
};
