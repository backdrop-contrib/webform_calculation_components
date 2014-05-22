(function($, Drupal)
/**
 * @file
 * JavaScript behaviors for the calculation of selected webform component numbers.
 */
{
	// Our function name is prototyped as part of the Drupal.ajax namespace, adding to the commands:
	Drupal.ajax.prototype.commands.webformCalcHiddenComponentAjaxCallback = function(ajax, response, status)
	{
		// The value we passed in our Ajax callback function will be available inside the
		// response object. Since we defined it as selectedValue in our callback, it will be
		// available in response.selectedValue. Usually we would not use an alert() function
		// as we could use ajax_command_alert() to do it without having to define a custom
		// ajax command, but for the purpose of demonstration, we will use an alert() function
		// here:
        console.log("response %o",response);
        //alert("hello from Webofm calculation Hidden component ajax commands");
        var operation = response.webformOperationDataArray['operation'];
        var result_id = '#'+response.webformOperationDataArray['result_id'];
        var operation_result = 0;
        var operand_ids = response.webformOperationDataArray['operand_ids'];
        var operand_id = '';
        for (var i = 0; i < operand_ids.length; i++) {
          operand_id = '#'+operand_ids[i];
          switch(operation) {
            case 'addition':
            operation_result = Number($(result_id).val()) + Number($(operand_id).val());
            break;
            case 'subtraction':
            operation_result = Number($(result_id).val()) - Number($(operand_id).val());
            break;
            case 'multiplication':
            operation_result = Number($(result_id).val()) * Number($(operand_id).val());
            break;
            case 'division':
            operation_result =  Number($(result_id).val()) / ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
            break;
            case 'percentage':
            operation_result = 0.01 * Number($(result_id).val()) * Number($(operand_id).val());
            break;
            case 'modulo':
            operation_result =  Math.floor(Number($(result_id).val())) % ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
            break;
          }
          $(result_id).val(operation_result);
        }
        //console.log("operand_ids > %o",operand_ids);
        //console.log("operation > %o",operation);
        //console.log("result_id > %o",$(result_id).val());
	};
}(jQuery, Drupal));
