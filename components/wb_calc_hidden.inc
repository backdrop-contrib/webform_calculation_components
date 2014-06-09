<?php
/**
 * @file
 * This defines the webform helper callbacks for the webform component
 * calculation hidden.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_wb_calc_hidden() {
  $default_component_values = array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'extra' => array(
      'private' => FALSE,
      'calculation_hidden_type' => 'value',
      'analysis' => FALSE,
      'operand_field' => '',
      'operation_type' => '',
      'select_field' => '',
      'select_field_choices' => '',
      'result_field' => '',
      'cumulative_result' => '',
      'attributes' => array(),
    ),
  );
  return $default_component_values;
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_wb_calc_hidden() {
  return array(
    'webform_display_wb_calc_hidden' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_wb_calc_hidden($component) {
  $form = array();
  $webformnode = node_load($component['nid']);
  $available_numeric_fields = array();
  $available_select_fields = array();
  $available_select_fields_choices = array();
  foreach ($webformnode->webform['components'] as $component_element) {
    if ($component_element['type'] == 'number' || $component_element['type'] == 'wb_calc_number') {
      $available_numeric_fields[$component_element['form_key']] = $component_element['name'];
    }
    if ($component_element['type'] == 'select') {
      $available_select_fields[$component_element['form_key']] = $component_element['name'];
      $available_select_fields_choices[$component_element['form_key']] = _webform_select_options_from_text($component_element['extra']['items'], FALSE);
    }
  }

  $form['value'] = array(
    '#type' => 'textarea',
    '#title' => t('Default value'),
    '#default_value' => $component['value'],
    '#description' => t('The default value of the field.') . ' ' . theme('webform_token_help'),
    '#cols' => 60,
    '#rows' => 5,
    '#weight' => 0,
  );

  $form['display']['calculation_hidden_type'] = array(
    '#type' => 'radios',
    '#options' => array(
      'value' => t('Secure value (allows use of all tokens)'),
      'hidden' => t('Hidden element (less secure, changeable via JavaScript)'),
    ),
    '#title' => t('Webform hidden calculation type'),
    '#description' => t('Both types of webform hidden calculation fields are not shown to end-users. Using a <em>Secure value</em> allows the use of <em>all tokens</em>, even for anonymous users.'),
    '#default_value' => $component['extra']['calculation_hidden_type'],
    '#parents' => array('extra', 'calculation_hidden_type'),
  );

  $form['extra']['operand_field'] = array(
    '#type' => 'select',
    '#default_value' => $component['extra']['operand_field'],
    '#title' => t('Operand field'),
    '#multiple' => TRUE,
    '#size' => 2,
    '#options' => $available_numeric_fields,
    '#description' => t('Select the numeric component or components as operand fields. Hold Control key to select more than one.'),
    '#parents' => array('extra', 'operand_field'),
  );

  $form['extra']['operation_type'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#default_value' => $component['extra']['operation_type'],
    '#options' => array(
      'addition' => t('Addition') . ' (+)',
      'subtraction' => t('Subtraction') . ' (-)',
      'multiplication' => t('Multiplication') . ' (*)',
      'division' => t('Division') . ' (/)',
      'percentage' => t('Percentage'),
      'modulo' => t('Modulo'),
    ),
    '#description' => t('E.g. Addition, Multiplication etc.'),
    '#parents' => array('extra', 'operation_type'),
  );

  $form['extra']['select_field'] = array(
    '#type' => 'select',
    '#default_value' => $component['extra']['select_field'],
    '#title' => t('Select field for calculation'),
    '#options' => $available_select_fields,
    '#description' => t('Choose a select component to perform the calculation.'),
    '#parents' => array('extra', 'select_field'),
  );

  $form['extra']['select_field_choices'] = array(
    '#type' => 'select',
    '#default_value' => $component['extra']['select_field_choices'],
    '#title' => t('Select values that enable the calculation'),
    '#options' => $available_select_fields_choices,
    '#multiple' => TRUE,
    '#description' => t('Choose which values of the select field will enable the calculation. Hold Control key to select more than one.'),
    '#parents' => array('extra', 'select_field_choices'),
  );

  $form['extra']['result_field'] = array(
    '#type' => 'select',
    '#default_value' => $component['extra']['result_field'],
    '#title' => t('Result field'),
    '#options' => $available_numeric_fields,
    '#description' => t('Select the numeric component as the result field or target of the operation.'),
    '#parents' => array('extra', 'result_field'),
  );

  $form['extra']['cumulative_result'] = array(
    '#type' => 'select',
    '#title' => t('Cumulative result'),
    '#default_value' => $component['extra']['cumulative_result'],
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#description' => t('Whether the current value of the result field is included in the calculation or not.'),
    '#parents' => array('extra', 'cumulative_result'),
  );

  return $form;
}

/**
 * Element validation callback. Ensure keys are not duplicated.
 */
function _webform_edit_validate_wb_calc_hidden($element, &$form_state) {
  // @to-do validate that select field choices coincide with the select field.
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_wb_calc_hidden($component, $value = NULL, $filter = TRUE) {
  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;

  $default_value = $filter ? webform_replace_tokens($component['value'], $node) : $component['value'];
  if (isset($value[0])) {
    $default_value = $value[0];
  }

  $element = array(
    '#title' => $filter ? NULL : $component['name'],
    '#weight' => $component['weight'],
    '#translatable' => array('title'),
  );

  if ($component['extra']['calculation_hidden_type'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }
  else {
    $element['#type'] = 'hidden';
    $element['#default_value'] = $default_value;

    /* Same-page conditionals depend on the wrapper around elements for getting
     * values. Wrap, but hide, the wrapper around hidden calculation elements.
     */
    $element['#theme_wrappers'] = array('webform_element');
    $element['#wrapper_attributes']['class'] = array();
    $element['#wrapper_attributes']['style'] = array('display: none');
  }

  if ($component['extra']['operand_field'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  if ($component['extra']['operation_type'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  if ($component['extra']['select_field'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  if ($component['extra']['select_field_choices'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  if ($component['extra']['result_field'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  if ($component['extra']['cumulative_result'] == 'value') {
    $element['#type'] = 'value';
    $element['#value'] = $default_value;
  }

  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_wb_calc_hidden($component, $value, $format = 'html') {
  $element = array(
    '#title' => $component['name'],
    '#markup' => isset($value[0]) ? $value[0] : NULL,
    '#weight' => $component['weight'],
    '#format' => $format,
    '#theme' => 'webform_display_wb_calc_hidden',
    '#theme_wrappers' => $format == 'text' ? array('webform_element_text') : array('webform_element'),
    '#translatable' => array('title'),
  );

  return $element;
}

/**
 * Theme function to render an wb_calc_hidden component.
 */
function theme_webform_display_wb_calc_hidden($variables) {
  $element = $variables['element'];

  return $element['#format'] == 'html' ? check_plain($element['#markup']) : $element['#markup'];
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_wb_calc_hidden($component, $sids = array()) {
  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
    ->fields('wsd', array('no', 'data'))
    ->condition('nid', $component['nid'])
    ->condition('cid', $component['cid']);

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $nonblanks = 0;
  $submissions = 0;
  $wordcount = 0;

  $result = $query->execute();
  foreach ($result as $data) {
    if (strlen(trim($data['data'])) > 0) {
      $nonblanks++;
      $wordcount += str_word_count(trim($data['data']));
    }
    $submissions++;
  }

  $rows[0] = array(t('Empty'), ($submissions - $nonblanks));
  $rows[1] = array(t('Non-empty'), $nonblanks);
  $other[0] = array(
    t('Average submission length in words (ex blanks)'), ($nonblanks != 0 ? number_format($wordcount / $nonblanks, 2) : '0'));

  return array(
    'table_rows' => $rows,
    'other_data' => $other,
  );
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_table_wb_calc_hidden($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_wb_calc_hidden($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $export_options['header_keys'] ? $component['form_key'] : $component['name'];
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_wb_calc_hidden($component, $export_options, $value) {
  return isset($value[0]) ? $value[0] : '';
}
