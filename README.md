# Webform Calculation Components

This module provides AJAX functionality to perform basic arithmetic operations
on webform components.

With this module the user can have calculated fields (e.g. the total amount,
calculated percentage etc.) This module provides two new component types:

 - **Webform Calculation Number** (Calculation - number)

That component is a numeric field where the user can type a number. The target
field (result field) is set when configuring the Webform Calculation Number
component.
When the webform is displayed, the user can enter numbers in these fields and
the calculation is performed against the result field.

 - **Webform Calculation Hidden** (Calculation - hidden)

It can be used to perform operations with existing numeric components.
The calculation is triggered when the user select a specific option in
checkboxes, radio button or select option.

All that is configured when creating the Webform calculation hidden component.
It is possible to perform one operation e.g. Addition to several numeric
fields, then the result will be calculated against the result number component.
Note that select field choices must be selected, (they can be more than one)
and they have to correspond to the select field that triggers the calculation.

The available operations are the following:

 - addition
 - subtraction
 - multiplication
 - division
 - percentage
 - modulo


## Installation

- Install this module using the official 
  [Backdrop CMS instructions](https://backdropcms.org/guide/modules)

## Configuration:

For Webform Calculation Number

Go to add content > webform (or any webform content type):
- Create a new webform
- Create new webform components, you need at least one numeric component to be
selected as the result field.
- Create a new Calculation - number component.
- Select the arithmetic operation and the result field.
- Optionally the number of decimals can be configured.
- Configure the rest of options like a normal webform component.

For Webform Calculation hidden

Go to add content > webform:
- Create a new webform
- Create new webform components, you need at least two numeric and a select
component.
- Create a new Calculation - hidden component.
- Select the first operand field. It has to be one or more of the numeric fields
created previously. Hold Control key to select more than one.
- Select the second operand field (optional). For non commutative operations
like subtraction, division and modulo the second operand has to be in the
second operand field. It can be one or more of the numeric fields created
previously. Hold Control key to select more than one. If you want to include
the current value of the result field in the calculation, include it in the
second operand field, that way it will be cumulative.
- Select the arithmetic operation and the result field.
- Select the select field (created previously).
- Select the select field choices. The choices must coincide with the chosen
select field options. Hold Control to key to select more than one.
- Select the result field, it has to be one of the numeric fields created
previously.
- Configure the rest of options like a normal webform component.

Notes:
- Division by zero is prevented internally.
- Nested webform components in fieldset are supported.

## Dependencies

- Webform 

## Issues

Bugs and Feature requests should be reported in the 
[Issue Queue](https://github.com/backdrop-contrib/webform_calculation_components/issues)

## Current Maintainers

- Seeking maintainer.

## Credits

- Ported to Backdrop CMS by [Laryn Kragt Bakker](https://github.com/laryn) - 
  [CEDC.org](https://cedc.org).
- Maintained for Drupal 7 by 
  [Anthony Goode](https://www.drupal.org/u/anthony-goode).

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory
for complete text.
