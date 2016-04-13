#!/usr/bin/perl

use Curses::UI;

my $val_wlan_id;
my $val_wlan_pwd;
my $val_SEND2DUSTI = 1;
my $val_SEND2MADAVI = 0;
my $val_SEND2MQTT = 0;
my $val_SEND2CSV = 0;
my $val_DHT22 = 0;
my $val_PPD = 1;
my $val_SDS = 0;

my $cui = new Curses::UI( -color_support => 1, -language => "de", -clear_on_exit => 1);

sub init_vars() {
	$val_wlan_id = 'Freifunk';
	$val_wlan_pwd = '';
	$val_SEND2DUSTI = 1;
	$val_SEND2MADAVI = 0;
	$val_SEND2MQTT = 0;
	$val_SEND2CSV = 0;

	$val_DHT22 = 0;
	$val_PPD = 1;
	$val_SDS = 0;
	$val_DISPLAY = 0;
	$val_DEBUG = 1;
}

sub write_ext_def() {
	open(OUTFILE,">","source/src/ext_def.h");
	print "Test";
	print OUTFILE '#define WLANSSID "'.$val_wlan_id."\"\n";
	print OUTFILE '#define WLANPWD "'.$val_wlan_pwd."\"\n";

	print OUTFILE '#define SEND2DUSTI '.($val_SEND2DUSTI ? '1' : '0')."\n";
	print OUTFILE '#define SEND2MADAVI '.($val_SEND2MADAVI ? '1' : '0')."\n";
	print OUTFILE '#define SEND2MQTT '.($val_SEND2MQTT ? '1' : '0')."\n";
	print OUTFILE '#define SEND2CSV '.($val_SEND2CSV ? '1' : '0')."\n";

	print OUTFILE '#define HOST_MQTT "mqtt.opensensors.io"'."\n";
	print OUTFILE '#define MQTT_PORT 1883'."\n";
	print OUTFILE '#define MQTT_USER ""'."\n";
	print OUTFILE '#define MQTT_PWD ""'."\n";
	print OUTFILE '#define MQTT_CLIENT_ID ""'."\n";
	print OUTFILE '#define MQTT_TOPIC ""'."\n";

	print OUTFILE '#define DHT_READ '.($val_DHT22 ? '1' : '0')."\n";
	print OUTFILE '#define DHT_PIN 13'."\n";
	print OUTFILE '#define DHT_TYPE DHT22'."\n";

	print OUTFILE '#define PPD_READ '.($val_PPD ? '1' : '0')."\n";
	print OUTFILE '#define PPD_PIN_PM1 12'."\n";
	print OUTFILE '#define PPD_PIN_PM2 14'."\n";

	print OUTFILE '#define SDS_READ '.($val_SDS ? '1' : '0')."\n";
	print OUTFILE '#define SDS_PIN_RX 5'."\n";
	print OUTFILE '#define SDS_PIN_TX 4'."\n";

	print OUTFILE '#define HAS_DISPLAY '.($val_DISPLAY ? '1' : '0')."\n";
	
	print OUTFILE '#define DEBUG '.($val_DEBUG ? '3' : '0')."\n";

	print OUTFILE '#define DEBUG_ERROR 1'."\n";
	print OUTFILE '#define DEBUG_WARNING 2'."\n";
	print OUTFILE '#define DEBUG_MIN_INFO 3'."\n";
	print OUTFILE '#define DEBUG_MED_INFO 4'."\n";
	print OUTFILE '#define DEBUG_MAX_INFO 5'."\n";

	close OUTFILE;
	$cui->delete('win1');
	$cui->leave_curses();
	print "Shell?\n";
	sleep(5);
	$cui->reset_curses();
	init_vars();
	main_window();
	$cui->draw();
	$cui->focus();
}

sub write_dialog() {
	my $return = $cui->dialog(
			-message   => "Wollen Sie den Sensor wirklich neu programmieren?",
			-title     => "Sind Sie sicher?", 
			-buttons   => ['yes', 'no'],
		);

	if ($return) { write_ext_def();};
}

sub exit_dialog_burn() {
	my $return = $cui->dialog(
			-message   => "Wollen Sie das Programm wirklich verlassen?",
			-title     => "Sind Sie sicher?", 
			-buttons   => ['yes', 'no'],
		);

	if ($return) { exit(0);};
}


sub main_window() {
	init_vars();
	my $win = $cui->add(
			'win1', 'Window',
			-border => 1,
			-centered => 1,
			-width => 60,
			-height => 25,
#			-y    => 1,
			-bfg  => 'red',
		);

	my $wlan_id_label = $win->add(
			'wlan_id_label', 'Label',
			-text => 'WLAN Name: ',
			-x => 2, -y => 1,
		);

	my $wlan_id = $win->add(
			'wlan_id', 'TextEntry',
			-text => $val_wlan_id,
			-showlines => 1,
			-maxlength => 24,
			-width => 25, 
			-x => 14, -y => 1,
			-onblur => sub { my $field = shift; $val_wlan_id = $field->get();},
		);
	$wlan_id->focus();

	my $wlan_pwd_label = $win->add(
			'wlan_pwd_label', 'Label',
			-text => 'WLAN Passwort: ',
			-x => 2, -y => 2,
		);

	my $wlan_pwd = $win->add(
			'wlan_pwd', 'PasswordEntry',
			-text => $val_wlan_pwd,
			-showlines => 1,
			-maxlength => 24,
			-width => 25,
			-x => 14, -y => 2,
			-onblur => sub { my $field = shift; $val_wlan_pwd = $field->get();},
		);

	my $checkbox_PPD = $win->add(
			'checkbox_PPD', 'Checkbox',
			-label => 'Sensor PPD42NS (Feinstaub, Standard)',
			-checked => $val_PPD,
			-x => 2, -y => 4,
			-onblur => sub { my $field = shift; $val_PPD = $field->get();},
		),

	my $checkbox_SDS = $win->add(
			'checkbox_SDS', 'Checkbox',
			-label => 'Sensor SDS011 (Feinstaub, optional)',
			-checked => $val_SDS,
			-x => 2, -y => 5,
			-onblur => sub { my $field = shift; $val_SDS = $field->get();},
		);

	my $checkbox_DHT22 = $win->add(
			'checkbox_DHT22', 'Checkbox',
			-label => 'Sensor DHT22 (Temperatur ,Luftfeuchte, optional)',
			-checked => $val_DHT22,
			-x => 2, -y => 6,
			-onblur => sub { my $field = shift; $val_DHT22 = $field->get();},
		);

	my $checkbox_LUFTDATEN = $win->add(
			'checkbox_LUFTDATEN', 'Checkbox',
			-label => 'Senden an Luftdaten-API (Standard)',
			-checked => $val_SEND2DUSTI,
			-x => 2, -y => 8,
			-onblur => sub { my $field = shift; $val_SEND2DUSTI = $field->get();},
		);

	my $checkbox_MADAVI = $win->add(
			'checkbox_MADAVI', 'Checkbox',
			-label => 'Senden an Madavi-API (optional)',
			-checked => $val_SEND2MADAVI,
			-x => 2, -y => 9,
			-onblur => sub { my $field = shift; $val_SEND2MADAVI = $field->get();},
		);

	my $checkbox_DISPLAY = $win->add(
			'checkbox_DISPLAY', 'Checkbox',
			-label => 'Display vorhanden (optional)',
			-checked => $val_DISPLAY,
			-x => 2, -y => 11,
			-onblur => sub { my $field = shift; $val_DISPLAY = $field->get();},
		);

	my $checkbox_DEBUG = $win->add(
			'checkbox_DEBUG', 'Checkbox',
			-label => 'Debug Ausgabe via USB (empfohlen zu Fehlersuche)',
			-checked => $val_DEBUG,
			-x => 2, -y => 12,
			-onblur => sub { my $field = shift; $val_DEBUG = $field->get();},
		);

	my $buttons = $win->add(
			'buttons', 'Buttonbox',
			-buttons   => [{
				-label => '< Firmware schreiben >',
				-value => 1,
				-shortcut => B,
				-onpress =>  \&write_dialog,
			},{ 
				-label => '< Programm verlassen >',
				-value => 2,
				-shortcut => X,
				-onpress => \&exit_dialog_burn, 
			}],
			-x => 2, -y => 14,
		);

	my $helptext1 = $win->add(
			'helptext1', 'Label',
			-text => '[TAB] zum Wechseln zwischen den Feldern',
			-x => 2, -y => 16,
		);

	my $helptext2 = $win->add(
			'helptext2', 'Label',
			-text => '[SPACE] Markieren der Auswahlfelder',
			-x => 2, -y => 17,
		);

}

main_window();

$cui->mainloop();
