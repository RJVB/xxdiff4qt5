/* -*- c-file-style: "xxdiff" -*- */
/******************************************************************************\
 * $RCSfile$
 *
 * Copyright (C) 1999-2003  Martin Blais <blais@furius.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 ******************************************************************************/

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

#include <markers.h>

#include <QtGui/QFileDialog>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QDir>

#include <QtGui/QRadioButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QCheckBox>

#include <QtGui/QLayout>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

XX_NAMESPACE_BEGIN

/*==============================================================================
 * PUBLIC FUNCTIONS
 *============================================================================*/

/*==============================================================================
 * CLASS XxMarkersWidget
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxMarkersWidget::XxMarkersWidget( 
   bool     threeWay,
   QWidget* parent
) :
   BaseClass( parent )
{
    setupUi( this );

   // Make connections.
   connect( _checkboxConflicts, SIGNAL( clicked() ),
            this, SLOT( onConflicts() ) );
   connect( _checkboxConditionals, SIGNAL( clicked() ),
            this, SLOT( onConditionals() ) );

   if ( ! threeWay ) {
      _lineeditConditional3->hide();
      _labelConditional3->hide();
   }

   _checkboxConflicts->setChecked( true );
   onConflicts();
}

//------------------------------------------------------------------------------
//
void XxMarkersWidget::onConflicts()
{
   _lineeditConditional1->setEnabled( false );
   _labelConditional1->setEnabled( false );
   _lineeditConditional2->setEnabled( false );
   _labelConditional2->setEnabled( false );
   _lineeditConditional3->setEnabled( false );
   _labelConditional3->setEnabled( false );
   _removeEmptyConditionals->setEnabled( false );
}

//------------------------------------------------------------------------------
//
void XxMarkersWidget::onConditionals()
{
   _lineeditConditional1->setEnabled( true );
   _labelConditional1->setEnabled( true );
   _lineeditConditional2->setEnabled( true );
   _labelConditional2->setEnabled( true );
   _lineeditConditional3->setEnabled( true );
   _labelConditional3->setEnabled( true );
   _removeEmptyConditionals->setEnabled( true );
}

//------------------------------------------------------------------------------
//
bool XxMarkersWidget::useConditionals() const
{
   return _checkboxConditionals->isChecked();
}

//------------------------------------------------------------------------------
//
bool XxMarkersWidget::removeEmptyConditionals() const
{
   return _removeEmptyConditionals->isChecked();
}

//------------------------------------------------------------------------------
//
QString XxMarkersWidget::getConditionalVariable1() const
{
   return _lineeditConditional1->text();
}

//------------------------------------------------------------------------------
//
QString XxMarkersWidget::getConditionalVariable2() const
{
   return _lineeditConditional2->text();
}

//------------------------------------------------------------------------------
//
QString XxMarkersWidget::getConditionalVariable3() const
{
   return _lineeditConditional3->text();
}

/*==============================================================================
 * CLASS XxMarkersDialog
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxMarkersDialog::XxMarkersDialog(
   const bool  threeWay,
   QWidget*    parent
) :
   BaseClass( parent )
{
   //resize( 627, 262 ); 
   //setCaption( trUtf8( "Form1" ) );
   QVBoxLayout* vlayout = new QVBoxLayout( this );
   vlayout->setMargin(11);
   vlayout->setSpacing(6);

   _markersWidget = new XxMarkersWidget( threeWay );
   vlayout->addWidget( _markersWidget );

   QHBoxLayout* hlayout = new QHBoxLayout;
   vlayout->addLayout( hlayout );
   hlayout->setMargin(0);
   hlayout->setSpacing(6);

   hlayout->addItem( new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

   _buttonOk = new QPushButton;
   _buttonOk->setText( trUtf8( "Ok" ) );
   _buttonOk->setDefault( TRUE );
   hlayout->addWidget( _buttonOk );
   hlayout->addItem( new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

   _buttonCancel = new QPushButton;
   _buttonCancel->setText( trUtf8( "Cancel" ) );
   hlayout->addWidget( _buttonCancel );
   hlayout->addItem( new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

   QObject::connect( _buttonOk, SIGNAL(clicked()), this, SLOT(accept()) );
   QObject::connect( _buttonCancel, SIGNAL(clicked()), this, SLOT(reject()) );
}

//------------------------------------------------------------------------------
//
void XxMarkersDialog::disableCancel()
{
   _buttonCancel->setEnabled( false );
}

//------------------------------------------------------------------------------
//
void XxMarkersDialog::reject()
{
   if ( _buttonCancel->isEnabled() ) {
      BaseClass::reject();
   }
   // else noop.
}

//------------------------------------------------------------------------------
//
bool XxMarkersDialog::getMarkers(
   bool        threeWay,
   bool&       useConditionals,
   bool&       removeEmptyConditionals,
   QString     conditionals[3],
   bool        noCancel,
   QWidget*    parent
)
{
   bool result = false;

   XxMarkersDialog* dlg = new XxMarkersDialog( threeWay, parent );
   if ( noCancel ) {
      dlg->disableCancel();
   }

   if ( dlg->exec() == QDialog::Accepted || noCancel ) {
      result = true;
   }

   useConditionals = dlg->_markersWidget->useConditionals();
   if ( useConditionals == true ) {
      conditionals[0] = dlg->_markersWidget->getConditionalVariable1();
      conditionals[1] = dlg->_markersWidget->getConditionalVariable2();
      conditionals[2] = dlg->_markersWidget->getConditionalVariable3();
   }
      
   removeEmptyConditionals = dlg->_markersWidget->removeEmptyConditionals();

   delete dlg;

   return result;
}

/*==============================================================================
 * CLASS XxMarkersFileDialog
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxMarkersFileDialog::XxMarkersFileDialog( 
   const QString& dirName,
   const QString& filter,
   bool           modal,
   bool           threeWay,
   QWidget*       parent
) :
   BaseClass( parent, tr("Save as"), dirName, filter)
{
   setModal( modal );
   setAcceptMode( QFileDialog::AcceptSave );
   
   // Hack to embed XxMarkersWidget into the QFileDialog, since the
   // convenient Qt3 addWidgets doesn't exist anymore
   QVBoxLayout *l = qFindChild<QVBoxLayout*>(this);
   Q_ASSERT(l);
   _markersWidget = new XxMarkersWidget( threeWay );
   l->addWidget(_markersWidget);
}

//------------------------------------------------------------------------------
//
QString XxMarkersFileDialog::getSaveFileName( 
   const QString& startWith,
   const QString& filter,
   bool           threeWay,
   bool&          useConditionals,
   bool&          removeEmptyConditionals,
   QString        conditionals[3],
   QWidget*       parent
)
{
   XxMarkersFileDialog* dlg = new XxMarkersFileDialog(
      startWith, filter, TRUE, threeWay, parent
   );

   QString result;
   dlg->setFileMode( QFileDialog::AnyFile );

   if ( dlg->exec() == QDialog::Accepted ) {
      result = dlg->selectedFiles().first();
   }

   //XxMarkersWidget* markers = dlg->getMarkersWidget();
   useConditionals = dlg->_markersWidget->useConditionals();
   if ( useConditionals == true ) {
      conditionals[0] = dlg->_markersWidget->getConditionalVariable1();
      conditionals[1] = dlg->_markersWidget->getConditionalVariable2();
      conditionals[2] = dlg->_markersWidget->getConditionalVariable3();
   }

   removeEmptyConditionals = dlg->_markersWidget->removeEmptyConditionals();

   delete dlg;

   return result;
}

XX_NAMESPACE_END
