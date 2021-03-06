<?php
/**
 * Returns a json object of fields
 *
 * @Resource URL
 * /api/node/ [sample: /api/node/1]
 *
 * @param $id
 * The node id
  */
function getNode($id) {

  $fields = node_load($id);

  $fields->custom_fields = array();
  $fields->composed_fields = array();
  foreach ($fields as $field => $value) {
    if (strpos($field, 'field_') !== FALSE && !empty($value)) {

      //get field information and field type to manage composed fields
      $field_info = field_info_field($field);
      $field_type = $field_info['type'];
      if ($field_type === 'composed_field') {
      //if (strpos($field, '_composed') !== FALSE) {
        _manageComposed($field, $fields);
      } else {
        $fields->custom_fields[$field] = field_view_field('node', $fields, $field)['#items'][0];
      }
      //unset the old values
      unset($fields->$field);
    }
    if ($field === 'body') {
      $fields->body = field_view_field('node', $fields, 'body')['#items'][0];
    }
  }

  if (empty($fields->custom_fields)) {
    //no custom fields so unset the propety
    unset($fields->custom_fields);
  }


  //get rid of some properties you dont need
  unset($fields->rdf_mapping);


  //return field_info_instance_settings('composed_field');
  //return field_info_field_by_id($field_id = 7);
  // return field_info_fields();
  //return field_info_field_settings($type = 'composed_field');
  //return field_info_field('field_test_composed');

  //THIS GIVES ME THE SETTINGS!!
  //return field_info_instance($entity_type='node', $field_name='field_test_composed', $bundle_name='page');

  return $fields;

}

/**
 * When using Composed Fields always name them including the string '_composed'
 * This will run through them and give URI's for images and make it friendlier
 * to work with. (e.g. unserializes the array for you)
 */
function _manageComposed($field, $fields) {

  //THIS GIVES YOU INFORMATION ABOUT THE COMPOSED FIELD
  $types = field_info_instance($entity_type='node', $field_name=$field, $bundle_name='page')['widget']['settings']['composed_field']['type'];
  $titles = field_info_instance($entity_type='node', $field_name=$field, $bundle_name='page')['widget']['settings']['composed_field']['title'];

  //$raw = field_view_field('node', $fields, $field)['#items'];

  $composed_field = field_view_field('node', $fields, $field);
  $composed = array();
  $output = array();

  if (!isset($composed_field['#items'])) {
    return $fields->composed_fields[$field] = 0;
  }

  foreach($composed_field['#items'] as $ktop => $vtop) {

    $composed[$ktop] = unserialize(field_view_field('node', $fields, $field)['#items'][$ktop]['composed']);

    //set titles and get file uri
    foreach ($types as $k => $v) {

      $title = strtolower($titles[$k]['value']);
      $title = str_replace(' ', '_', $title);

      $output[$ktop][$title] = $composed[$ktop][$k];


      if ($v['value'] === "managed_file") {
        $file = file_load($composed[$ktop][$k]);
        if (isset($file->uri)) {
          $output[$ktop]['file_uri'] = file_create_url($file->uri);
        }
      }

    }

  }

  //HANDLE MORE THAN ONE? RIGHT NOW IT ONLY HANDLES ONE??
  return $fields->composed_fields[$field] = $output;

}






