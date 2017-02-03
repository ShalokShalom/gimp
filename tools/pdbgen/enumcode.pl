#!/usr/bin/perl -w

# GIMP - The GNU Image Manipulation Program
# Copyright (C) 1999-2003 Manish Singh <yosh@gimp.org>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUTFILE ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

BEGIN {
    $srcdir   = $ENV{srcdir}  || '.';
    $destdir  = $ENV{destdir} || '.';
    $builddir = $ENV{builddir} || '.';
}

use lib $srcdir;

require 'enums.pl';
require 'util.pl';

*enums = \%Gimp::CodeGen::enums::enums;

*write_file = \&Gimp::CodeGen::util::write_file;
*FILE_EXT   = \$Gimp::CodeGen::util::FILE_EXT;

my $enumfile = "$builddir/libgimp/gimpenums.h$FILE_EXT";
open ENUMFILE, "> $enumfile" or die "Can't open $enumfile: $!\n";

print ENUMFILE <<'LGPL';
/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is autogenerated by enumcode.pl */

LGPL

my $guard = "__GIMP_ENUMS_H__";
print ENUMFILE <<HEADER;
#ifndef $guard
#define $guard

G_BEGIN_DECLS

HEADER

foreach (sort keys %enums) {
    if (! ($enums{$_}->{header} =~ /libgimp/)) {
        my $gtype = $func = $_;

	for ($gtype) { s/Gimp//; s/([A-Z][^A-Z]+)/\U$1\E_/g; s/_$// }
	for ($func) { s/Gimp//; s/([A-Z][^A-Z]+)/\L$1\E_/g; s/_$// }

	print ENUMFILE "\n#define GIMP_TYPE_$gtype (gimp_$func\_get_type ())\n\n";
	print ENUMFILE "GType gimp_$func\_get_type (void) G_GNUC_CONST;\n\n";
	print ENUMFILE "typedef enum\n{\n";

	my $enum = $enums{$_}; my $body = "";

	foreach $symbol (@{$enum->{symbols}}) {
	    my $sym = $symbol;
	    $body .= "  $sym";
	    $body .= " = $enum->{mapping}->{$symbol}" if !$enum->{contig};
	    $body .= ",\n";
	}

	$body =~ s/,\n$//s;
	$body .= "\n} ";
	$body .= "$_;\n\n";
	print ENUMFILE $body
    }
}

print ENUMFILE <<HEADER;

void           gimp_enums_init           (void);

const gchar ** gimp_enums_get_type_names (gint *n_type_names);


G_END_DECLS

#endif /* $guard */
HEADER

close ENUMFILE;
&write_file($enumfile, "$destdir/libgimp");

$enumfile = "$builddir/libgimp/gimpenums.c.tail$FILE_EXT";
open ENUMFILE, "> $enumfile" or die "Can't open $enumfile: $!\n";

print ENUMFILE <<CODE;

typedef GType (* GimpGetTypeFunc) (void);

static const GimpGetTypeFunc get_type_funcs[] =
{
CODE

my $first = 1;
foreach (sort keys %enums) {
    if (! ($_ =~ /GimpUnit/)) {
	my $enum = $enums{$_};
	my $func = $_;

	for ($func) { s/Gimp//; s/PDB/Pdb/; s/([A-Z][^A-Z]+)/\L$1\E_/g; s/_$// }

	print ENUMFILE ",\n" unless $first;
	print ENUMFILE "  gimp_$func\_get_type";

	$first = 0;
    }
}
print ENUMFILE "\n" unless $first;

print ENUMFILE <<CODE;
};

static const gchar * const type_names[] =
{
CODE

$first = 1;
foreach (sort keys %enums) {
    if (! ($_ =~ /GimpUnit/)) {
	my $enum = $enums{$_};
	my $gtype = $_;

	print ENUMFILE ",\n" unless $first;
	print ENUMFILE "  \"$gtype\"";

        $first = 0;
    }
}
print ENUMFILE "\n" unless $first;

print ENUMFILE <<CODE;
};

static gboolean enums_initialized = FALSE;

GType gimp_layer_mode_effects_get_type (void);

/**
 * gimp_enums_init:
 *
 * This function makes sure all the enum types are registered
 * with the #GType system. This is intended for use by language
 * bindings that need the symbols early, before gimp_main is run.
 * It's not necessary for plug-ins to call this directly, because
 * the normal plug-in initialization code will handle it implicitly.
 *
 * Since: 2.4
 **/
void
gimp_enums_init (void)
{
  const GimpGetTypeFunc *funcs = get_type_funcs;
  GQuark                 quark;
  gint                   i;

  if (enums_initialized)
    return;

  for (i = 0; i < G_N_ELEMENTS (get_type_funcs); i++, funcs++)
    {
      GType type = (*funcs) ();

      g_type_class_ref (type);
    }

  /*  keep compat enum code in sync with app/app.c (app_libs_init)  */
  quark = g_quark_from_static_string ("gimp-compat-enum");

  g_type_set_qdata (GIMP_TYPE_LAYER_MODE, quark,
		    (gpointer) gimp_layer_mode_effects_get_type ());

  enums_initialized = TRUE;
}

/**
 * gimp_enums_get_type_names:
 * \@n_type_names: return location for the number of names
 *
 * This function gives access to the list of enums registered by libgimp.
 * The returned array is static and must not be modified.
 *
 * Return value: an array with type names
 *
 * Since: 2.2
 **/
const gchar **
gimp_enums_get_type_names (gint *n_type_names)
{
  g_return_val_if_fail (n_type_names != NULL, NULL);

  *n_type_names = G_N_ELEMENTS (type_names);

  return (const gchar **) type_names;
}
CODE

close ENUMFILE;
&write_file($enumfile, "$destdir/libgimp");
