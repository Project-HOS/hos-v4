

				
				.extern	_start
				.extern	_stack_end
				
				
				.section	.vector
				
				.long	_start			/* �ѥ����ꥻ�å� */
				.long	_stack_end
				.long	_start			/* �ޥ˥奢��ꥻ�å� */
				.long	_stack_end

				.end

