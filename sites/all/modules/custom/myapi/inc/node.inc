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

      //manage composed fields here for now...
      //HAS TO BE NAMED WITH '_composed' in the name!!
      //GET THE FIELD INFORMATION SEE BELOW SO THIS ISNT A REQUIREMENT!!!
      if (strpos($field, '_composed') !== FALSE) {
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

  $raw = field_view_field('node', $fields, $field)['#items'];
  $composed = unserialize(field_view_field('node', $fields, $field)['#items'][0]['composed']);
  //THIS GIVES YOU INFORMATION ABOUT THE COMPOSED FIELD
  $types = field_info_instance($entity_type='node', $field_name='field_test_composed', $bundle_name='page')['widget']['settings']['composed_field']['type'];

  // $count = 0;
  // foreach($types as $key => $type) {
  //   $count++;
  //   if ($type['value'] === 'managed_file') {
  //     //get the uri from the image ID!
  //     $file = file_load($composed[$count]);
  //     $file_path = $file->uri;
  //
  //     $composed['uri'] = file_create_url($file_path);
  //   }
  // }

  //HANDLE MORE THAN ON RIGHT NOW IT ONLY HANDLES ONE
  $fields->composed_fields[$field] = $raw;
}






